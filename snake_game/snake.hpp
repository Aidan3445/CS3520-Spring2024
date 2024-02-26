/* snake.hpp -------
 *
 * Filename: snake.hpp
 * Description:
 * Author: Adeel Bhutta
 * Maintainer:
 * Created: Sun Sep 13 21:01:02 2022
 * Last-Updated: September 13 22:43 2022
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 * - Added a method to find the previous direction
 * - Added a move method to snake
 * - Added an eat_food method to change the snake's size
 *   based on the food that was eaten
 * - Added method to grow snake by 1
 * - Added method to check if the snake is out of bounds
 * - added method to check if snake is on a given x and y position at any point in the tail
 */

/* Copyright (c) 2022 Adeel Bhutta
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */
#include "food.hpp"
#include <cstdbool>

struct Snake {
  int x;
  int y;
  int speed;
  char color[3];
  char symbol;
  struct Snake* next;
  // Added Methods
  /**
   * Moves the snake to the given new x and y position.
   */
  void move(const int &new_x, const int &new_y);
};

typedef struct Snake Snake;

Snake* init_snake(int x, int y);
Snake* create_tail(int x, int y);
Snake* move_snake(Snake* snake, int direction);
void draw_snake(Snake* snake);
bool eat_itself(Snake* snake);
Snake* remove_tail(Snake* snake);
int len(Snake* snake);
// Added Methods
/**
 * Returns the previous direction the snake was moving in.
 * If snake is only 1 long, returns NOCHAR
 */
int prev_dir(Snake *snake);
/**
 * Changes the given snake's size based on the food that was eaten.
 */
void eat_food(Snake *snake, enum Type food);
/**
 * Adds a tail to the snake.
 */
Snake* grow(Snake *snake);
/**
 * Returns true if the snake is out of bounds.
 */
bool out_of_bounds(Snake* snake, const int &x_offset, const int &y_offset, const int &width, const int &height);
/**
 * deallocates the memory used by the snake 
 */
void free_snake(Snake* snake);
/**
 * Returns true if the snake exists at the given x and y position
 * as well as a given radius around the head.
 */
bool snake_exists(Snake *snake, int x, int y, unsigned int radius = 0);

