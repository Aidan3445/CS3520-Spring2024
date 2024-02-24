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
  *food_x = rand() % width + x_offset;
  *food_y = rand() % height + y_offset;
}
void game() {
  enum State state = INIT;       // Set the initial state
  static int x_max, y_max;       // Max screen size variables
  static int x_offset, y_offset; // distance between the top left corner of your
                                 // screen and the start of the board
  gamewindow_t *window;          // Name of the board
  Snake *snake;                  // The snake
  Food *foods, *new_food;        // List of foods (Not an array)

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
  double speedRatio = 0.75;
  int speedCounter = 1;

  while (true) {
    switch (state) {
    case INIT:
      srand(time(nullptr)); // Initializes random seed
      initscr();
      start_color();
      nodelay(stdscr, TRUE); // Dont wait for char
      noecho();              // Don't echo input chars
      getmaxyx(stdscr, y_max, x_max);
      keypad(stdscr, TRUE); // making keys work
      curs_set(0);          // hide cursor
      timeout(100);

      // Setting height and width of the board
      x_offset = (x_max / 2) - (width / 2) - 12;
      y_offset = (y_max / 2) - (height / 2);

      // Init board
      window = init_GameWindow(x_offset, y_offset, width, height);
      draw_Gamewindow(window);

      // Init snake
      snake = init_snake(x_offset + (width / 2), y_offset + (height / 2));

      // Init foods
      int food_x, food_y, i;
      enum Type type;

      // Generate 20 foods
      generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
      type = random_food_type(); // Randomly deciding type of food
      foods = create_food(food_x, food_y, type);
      for (i = 1; i < 20; i++) {
        generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
        while (food_exists(foods, food_x, food_y) != None)
          generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
        type = random_food_type();
        new_food = create_food(food_x, food_y, type);
        add_new_food(foods, new_food);
      }
      // Generate 10 obstacles
      for (i = 0; i < 10; i++) {
        generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
        while (food_exists(foods, food_x, food_y) != None)
          generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
        new_food = create_food(food_x, food_y, Type::Death);
        add_new_food(foods, new_food);
      }
      state = START_MENU;
      break;

    case START_MENU:
      // Uses getch instead of get_char, since 's' is encoded to down in
      // get_char and we need to know if s or q have been pressed
      ch = getch();

      clear();
      draw_Gamewindow(window);
      draw_snake(snake);
      draw_food(foods);
      // draw start menu
      draw_start_menu(x_offset, y_offset, width, height);
      draw_score(score, x_offset, y_offset, width, height);

      // handle quit and start
      if (tolower(ch) == 'q') {
        state = EXIT;
        break;
      } else if (tolower(ch) == 's') {
        state = ALIVE;
        break;
      }
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

      if (type == Type::Death || out_of_bounds(snake, x_offset, y_offset, width, height) || eat_itself(snake)) {
        state = DEAD;
        break;
      }

      // check for food
      if (type != None) {
        eat_food(snake, type);
        // get food type to determine how to change snake size
        foods = remove_eaten_food(foods, snake->x, snake->y);
        // Adds a new food to replace the old one
        Food *new_food = create_food(0, 0, random_food_type());
        do {
          generate_points(&(new_food->x), &(new_food->y), width, height,
                          x_offset, y_offset);
        } while (food_exists(foods, new_food->x, new_food->y) != None);
        add_new_food(foods, new_food);

        // increase score
        int pointValue = score_added(type);
        score += pointValue;
        if (score < 0) {
          score = 0;
        }

        // increse frame rate to make game harder as score increases
        if (score / speedCounter >= 100) {
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
