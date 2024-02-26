/*game.cpp -------
 *
 * Filename: game.cpp
 * Description:
 * Author: Adeel Bhutta
 * Maintainer:
 * Created: Sat Sep 12 13:16:12 2022
 * Last-Updated: September 12 16:51 2022
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 * add pause state and menu
 * draw snake last so it is on top
 * increase score depending on food type
 * increase speed depending on score (every 100 points)
 * add lives
 * add a starting score to help keep track of points earned on each life
 * free memory of food and snake when respawning
 * add death screen
 *
 * fix food spawn to avoid edges and snake
 *
 *
 * COLORS!
 */

/*Copyright (c) 2022 Adeel Bhutta
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */
#include "game.hpp"
#include "food.hpp"
#include "game_window.hpp"
#include "key.hpp"
#include "snake.hpp"
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <utility>

void generate_points(int *food_x, int *food_y, int width, int height,
        int x_offset, int y_offset) {
    *food_x = rand() % (width - 1) + x_offset + 1;
    *food_y = rand() % (height - 1) + y_offset + 1;
}

void setDifficulty(int difficulty, Food** foods, Snake* snake, const int &width, const int &height, 
        const int &x_offset, const int &y_offset, timespec &timeret, unsigned int &protectionRadius) {
    // Set difficulty settings
    Food *new_food;
    int startingSpeed, foodCount, obstacleCount;
    switch (difficulty) {
        case 0:
            protectionRadius = 5;
            startingSpeed = 4;
            foodCount = 20;
            obstacleCount = 10;
            break;
        case 1:
            protectionRadius = 3;
            startingSpeed = 6;
            foodCount = 15;
            obstacleCount = 15;
            break;
        case 2:
            protectionRadius = 2;
            startingSpeed = 8;
            foodCount = 10;
            obstacleCount = 20;
            break;
        default:
            protectionRadius = 5;
            startingSpeed = 4;
            foodCount = 20;
            obstacleCount = 10;
            break;
    }

    // Init foods
    int food_x, food_y, i;
    enum Type type;

    // Generate 20 foods
    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
    type = random_food_type(); // Randomly deciding type of food
    *foods = create_food(food_x, food_y, type);
    for (i = 1; i < foodCount; i++) {
        generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
        while (food_exists(*foods, food_x, food_y) != None ||
                snake_exists(snake, food_x, food_y, protectionRadius))
            generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
        type = random_food_type();
        new_food = create_food(food_x, food_y, type);
        add_new_food(*foods, new_food);
    }
    // Generate 10 obstacles
    for (i = 0; i < obstacleCount; i++) {
        generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
        while (food_exists(*foods, food_x, food_y) != None ||
                snake_exists(snake, food_x, food_y, protectionRadius))
            generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
        new_food = create_food(food_x, food_y, Type::Death);
        add_new_food(*foods, new_food);
    }

    // Set speed
    timeret.tv_nsec = 999999999 / startingSpeed;
}

// initialize colors
void init_game_colors() {
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_YELLOW); // snake
    init_pair(2, COLOR_BLACK, COLOR_GREEN);   // growth food
    init_pair(3, COLOR_BLACK, COLOR_RED);     // shrink food
    init_pair(4, COLOR_BLACK, COLOR_WHITE);   // walls and death food
    init_pair(5, COLOR_BLACK, COLOR_CYAN);    // menu color
    init_pair(6, COLOR_BLACK, COLOR_RED);     // game over color
}

void game() {
    enum State state = INIT;       // Set the initial state
    static int x_max, y_max;       // Max screen size variables
    static int x_offset, y_offset; // distance between the top left corner of your
                                   // screen and the start of the board
    gamewindow_t *window;          // Name of the board
    Snake *snake;                  // The snake
    Food *foods;                   // List of foods (Not an array)
    enum Type type;                // food type reference

    const int height = 30;
    const int width = 70;
    char ch;

    // blinking timer for pause;
    // first int is pause length, second is time since pause started
    // time measured in frames defined by timeret below
    std::pair<int, int> pause_timer = std::make_pair(10, 10);

    struct timespec timeret;
    timeret.tv_sec = 0;
    timeret.tv_nsec = 999999999 / 4;

    // initialize score
    int score = 0;
    int starting_score = 0;
    double speedRatio = 0.75;
    int speedCounter = 1;
    int lives = 3;

    // difficulty settings
    int difficulty = 0;
    unsigned int protectionRadius = 5;

    while (true) {
        switch (state) {
            case INIT:
                srand(time(nullptr));  // Initializes random seed
                initscr();
                init_game_colors();         // Initializes colors
                nodelay(stdscr, TRUE); // Dont wait for char
                noecho();              // Don't echo input chars
                getmaxyx(stdscr, y_max, x_max);
                keypad(stdscr, TRUE);  // making keys work
                curs_set(0);           // hide cursor
                timeout(100);

                // Setting height and width of the board
                x_offset = (x_max / 2) - (width / 2) - 12;
                y_offset = (y_max / 2) - (height / 2);

                // Init board
                window = init_GameWindow(x_offset, y_offset, width, height);
                draw_Gamewindow(window);

                // Init snake
                snake = init_snake(x_offset + (width / 2), y_offset + (height / 2));

                // establish default difficulty settings
                setDifficulty(difficulty, &foods, snake, 
                        width, height, x_offset, y_offset, timeret, protectionRadius);

                state = START_MENU;
                break;

            case START_MENU:
                // Uses getch instead of get_char, since 's' is encoded to down in
                // get_char and we need to know if s or q have been pressed
                ch = getch();

                // handle quit and start keys
                // and set difficulty
                switch (tolower(ch)) {
                    case 'q':
                        state = EXIT;
                        break;
                    case 's':
                        state = ALIVE;
                        break;
                    case 5:
                    case 'd':
                        difficulty++;
                        if (difficulty > 2) {
                            difficulty = 0;
                        }
                        free_food(foods);
                        setDifficulty(difficulty, &foods, snake, 
                                width, height, x_offset, y_offset, timeret, protectionRadius);
                        break;
                    case 4:
                    case 'a':
                        difficulty--;
                        if (difficulty < 0) {
                            difficulty = 2;
                        }
                        free_food(foods);
                        setDifficulty(difficulty, &foods, snake, 
                                width, height, x_offset, y_offset, timeret, protectionRadius);
                        break;

                }
                score = 0;
                lives = 3;

                clear();
                draw_Gamewindow(window);
                draw_snake(snake);
                draw_food(foods);
                // draw start menu
                draw_start_menu(x_offset, y_offset, width, height, difficulty);
                draw_score(score, x_offset, y_offset, width, height);


                break;

            case ALIVE:
                ch = get_char();

                // handle quit and pause
                if (tolower(ch) == 'q') {
                    state = EXIT;
                    break;
                } else if (tolower(ch) == 'p') {
                    state = PAUSE;
                    break;
                }

                /* Write your code here */
                // pass ch to snake
                move_snake(snake, ch);

                type = food_exists(foods, snake->x, snake->y);

                // check for food
                if (type != None && type != Death) {
                    eat_food(snake, type);
                    // get food type to determine how to change snake size
                    foods = remove_eaten_food(foods, snake->x, snake->y);
                    // Adds a new food to replace the old one
                    Food *new_food = create_food(0, 0, random_food_type());
                    do {
                        generate_points(&(new_food->x), &(new_food->y), width, height,
                                x_offset, y_offset);
                    } while (food_exists(foods, new_food->x, new_food->y) != None ||
                            snake_exists(snake, new_food->x, new_food->y, protectionRadius));
                    add_new_food(foods, new_food);

                    // increase score
                    int pointValue = score_added(type);
                    score += pointValue;
                    if (score < 0) {
                        score = 0;
                    }

                    // increse frame rate to make game harder as score increases
                    if ((score - starting_score) / speedCounter >= 100) {
                        timeret.tv_nsec *= speedRatio;
                        speedCounter++;
                    }
                }
                
                // Draw everything on the screen
                clear();
                mvprintw(20, 20, "Key entered: %c", ch);
                draw_Gamewindow(window);
                draw_food(foods);
                draw_snake(snake);
                draw_score(score, x_offset, y_offset, width, height);

                // check for death
                // death cases:
                // - snake eats death food
                // - snake goes out of bounds
                // - snake eats itself
                // - snake is only 1 long, including null_tail (snake itself is never null)
                if (type == Death || snake->next == NULL ||
                        out_of_bounds(snake, x_offset, y_offset, width, height) || eat_itself(snake)) {
                    lives--;

                    state = DEAD;
                    break;
                }

                break;

            case PAUSE:
                // handle quit and resume keys
                ch = get_char();
                if (tolower(ch) == 'p') {
                    state = ALIVE;
                    pause_timer.second = pause_timer.first;
                    break;
                } else if (tolower(ch) == 'q') {
                    state = EXIT;
                    break;
                }

                if (pause_timer.second == pause_timer.first) {
                    clear();
                    pause_timer.second = 0;
                } else {
                    pause_timer.second++;
                    draw_Gamewindow(window);
                    draw_snake(snake);
                    draw_food(foods);
                }

                // draw pause menu
                draw_pause_menu(x_offset, y_offset, width, height);
                draw_score(0, x_offset, y_offset, width, height);
                break;

            case DEAD:
                ch = get_char();
                if (tolower(ch) == 'r') {
                    // delete snake and food
                    free_food(foods);
                    free_snake(snake);

                    // reset snake and food
                    snake = init_snake(x_offset + (width / 2), y_offset + (height / 2));
                    setDifficulty(difficulty, &foods, snake, 
                            width, height, x_offset, y_offset, timeret, protectionRadius);

                    // reset score and speed
                    starting_score = score;
                    speedCounter = 1;


                    // play again!
                    if (lives > 0) {
                        state = ALIVE;
                    } else {
                        starting_score = 0;

                        state = START_MENU;
                    }
                    break;
                } else if (tolower(ch) == 'q') {
                    state = EXIT;
                    break;
                }

                draw_Gamewindow(window);
                draw_food(foods);
                draw_snake(snake);
                draw_dead(lives, x_offset, y_offset, width, height);
                break;

            case EXIT:
                endwin();
                reset_shell_mode();
                printf("Thanks for playing!\n");
                return;
        }
        refresh();
        nanosleep(&timeret, NULL);
    }
}
