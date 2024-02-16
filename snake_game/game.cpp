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
*
*
*/

/*Copyright (c) 2022 Adeel Bhutta
*
* All rights reserved.
*
* Additional copyrights may follow
*/
#include <cctype>
#include <ncurses.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <string>
#include "snake.hpp"
#include "food.hpp"
#include "game_window.hpp"
#include "key.hpp"
#include "game.hpp"
void generate_points(int *food_x, int *food_y, int width, int height, int x_offset, int y_offset){
    *food_x = rand() % width + x_offset;
    *food_y = rand() % height + y_offset;
}
void game(){
    enum State state = INIT; // Set the initial state
    static int x_max, y_max; //Max screen size variables
    static int x_offset, y_offset; // distance between the top left corner of your screen and the start of the board
    gamewindow_t *window; // Name of the board
    Snake *snake; // The snake
    Food *foods,*new_food; // List of foods (Not an array)

    const int height = 30; 
    const int width = 70;
    char ch;

    // blinking timer for pause;
    // first int is pause length, second is time since pause started
    // time measured in frames defined by timeret below
    std::pair<int, int> pause_timer = std::make_pair(10, 0);

    struct timespec timeret;
    timeret.tv_sec = 0;
    timeret.tv_nsec = 999999999/60;

    while(true){
        switch(state){
        case INIT:
            initscr();
            start_color();
            nodelay(stdscr, TRUE); //Dont wait for char
            noecho(); // Don't echo input chars
            getmaxyx(stdscr, y_max, x_max);
            keypad(stdscr, TRUE); // making keys work
            curs_set(0); // hide cursor
            timeout(100);

            // Setting height and width of the board
            x_offset = (x_max / 2) - (width / 2);
            y_offset = (y_max / 2) - (height / 2);
            
            //Init board
            window = init_GameWindow(x_offset, y_offset, width, height);
            draw_Gamewindow(window);

            // Init snake
            snake = init_snake(x_offset + (width / 2), y_offset + (height / 2));
            
            // Init foods
            int food_x, food_y, i;
            enum Type type;

            //Generate 20 foods
            generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
            type = (rand() > RAND_MAX/2) ? Increase : Decrease; // Randomly deciding type of food
            foods = create_food(food_x, food_y, type);
            for(i = 1; i < 20; i++){
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                while (food_exists(foods,food_x, food_y))
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                type = (rand() > RAND_MAX/2) ? Increase : Decrease;
                new_food = create_food(food_x, food_y, type);
                add_new_food(foods, new_food);
            }
            state = ALIVE;
            break;

        case ALIVE:
            ch = get_char();

            // handle quit and pause
            if(tolower(ch) == 'q') {
                state = EXIT;
                break; 
            }
            else if(tolower(ch) == 'p'){
                state = PAUSE;
                break;
            }
            
            /* Write your code here */
            // pass ch to snake
            move_snake(snake, ch);
            // if ch is q, quit
            // if ch is p, pause
                // handling of pause menu

			// Draw everything on the screen
            clear();
            mvprintw(20,20, "Key entered: %i", ch);
            draw_Gamewindow(window);
            draw_snake(snake);
            draw_food(foods);
            break;

        case PAUSE:
            // handle quit and resume keys
            ch = get_char();
            if(tolower(ch) == 'p') {
                state = ALIVE;
                break;
            }
            else if(tolower(ch) == 'q') {
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
            break;

        case DEAD:
            endwin();
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
