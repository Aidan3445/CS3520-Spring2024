/* snake.cpp -------
 *
 * Filename: snake.cpp
 * Description:
 * Author: Adeel Bhutta
 * Maintainer:
 * Created: Sun Sep 13 9:12:30 2022
 * Last-Updated: September 13 22:40 2022
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 *
 * - Updated remove_tail to prevent removing a tail if the snake is at length 2
 *   (which prevents a segmentation fault if you try to remove a tail when the
 *   snake is length 1)
 *   |-> Also, since length 2 is the minimum length for the game to function properly
 * - draw snake does not print the null_tail
 *
 *   delete snake
 */

/* Copyright (c) 2022 Adeel Bhutta
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

#include "snake.hpp"
#include "key.hpp"
#include <cstdbool>
#include <cstdlib>
#include <cstring>
#include <ncurses.h>

// Initialize snake
Snake* init_snake(int x, int y) {
	Snake* head = create_tail(x, y);
	Snake* tail1 = create_tail(x - 1, y);
	Snake* tail2 = create_tail(x - 2, y);
	Snake* null_tail = create_tail(x - 3, y);
	tail2->next = null_tail;
	tail1->next = tail2;
	head->next = tail1;
	return head;
}

// Creates one tail
Snake* create_tail(int x, int y) {
	Snake* snake = new Snake;
	snake->symbol = '#';
	snake->next = NULL;
	snake->x = x;
	snake->y = y;
	return snake;
}

int prev_dir(Snake* snake) {
	if (snake->next != NULL) {
		int x_dif = snake->x - snake->next->x;
		if (x_dif < 0) {
			return LEFT;
		} else if (x_dif > 0) {
			return RIGHT;
		}
		int y_dif = snake->y - snake->next->y;
		if (y_dif < 0) {
			return UP;
		} else if (y_dif > 0) {
			return DOWN;
		}
	}
	return NOCHAR;
}

void eat_food(Snake* snake, enum Type food) {
	int added = tails_added(food);
	for (int i = 0; i < added; i++) {
		grow(snake);
	}
	for (int i = 0; i > added; i--) {
		remove_tail(snake);
	}
}

void Snake::move(const int& new_x, const int& new_y) {
	if (next != NULL) {
		// Move next of snake, if it exists
		// to the previous position of it's prev
		next->move(x, y);
	}
	x = new_x;
	y = new_y;
}

// Moves the snake in the input direction
Snake* move_snake(Snake* snake, int direction) {
	if (direction > 4 || direction < 0) {
		direction = NOCHAR;
	}
	// TODO
	// Snake *new_head = new Snake;

	// Set the new head to have the x and y coordinates as the existing head of the snake
	int old_dir = prev_dir(snake);
	if (direction == UP && old_dir == DOWN || direction == DOWN && old_dir == UP ||
		direction == LEFT && old_dir == RIGHT || direction == RIGHT && old_dir == LEFT ||
		direction == NOCHAR) {
		// You can't turn 180 degrees
		direction = old_dir;
	}

	switch (direction) {
		case UP:
			// Write code to make the new head go up by 1 cell
			snake->move(snake->x, snake->y - 1);
			break;
		case DOWN:
			// Write code to make the new head go down by 1 cell
			snake->move(snake->x, snake->y + 1);
			break;
		case RIGHT:
			// Write code to make the new head go right by 1 cell
			snake->move(snake->x + 1, snake->y);
			break;
		case LEFT:
			// Write code to make the new head go left by 1 cell
			snake->move(snake->x - 1, snake->y);
			break;
	}

	// Set new head as the new head of the entire snake
	// Add all the features (color and symbol) to the new cell
	// Delete the tail from the snake: HINT - there is a remove tail function below


	return snake;
}

Snake* remove_tail(Snake* snake) {
	Snake* end = snake;
	if (!end->next) {
		return snake;
	}
	while (end->next->next) {
		end = end->next;
	}
	free(end->next);
	end->next = NULL;
	return snake;
}

Snake* grow(Snake* snake) {
	Snake* end = snake;
	while (end->next)
		end = end->next;
	// Adds a tail to the spot of the previous tail
	// So as the snake moves, the new tail pieces will show
	end->next = create_tail(end->x, end->y);
	return snake;
}

// draws the snake on the board
void draw_snake(Snake* snake) {
	// Since the final tail is just there to store the snake's
	// previous direction (and prevent any errors), we do not
	// print it
	attron(COLOR_PAIR(1));
	while (snake->next) {
		mvprintw(snake->y, snake->x, "%c", snake->symbol);
		snake = snake->next;
	}
	attroff(COLOR_PAIR(1));
}

// checks if it eats itself, if it does, then return true
bool eat_itself(Snake* snake) {
	// This is fine because we always have a null_tail,
	// so the snake has a min size of 2
	Snake* cur_tail = snake->next;
	while (cur_tail->next) {
		if (snake->x == cur_tail->x && snake->y == cur_tail->y) {
			return true;
		}
		cur_tail = cur_tail->next;
	}
	return false;
}

// ensure in bounds
bool out_of_bounds(
	Snake* snake, const int& x_offset, const int& y_offset, const int& width, const int& height) {
	// Checks if the snake is off the screen
	return (snake->x <= x_offset || snake->x >= width + x_offset) ||
		   (snake->y <= y_offset || snake->y >= height + y_offset);
}

// delete snake
void free_snake(Snake* snake) {
	Snake* cur_tail = snake;
	while (cur_tail) {
		Snake* next = cur_tail->next;
		delete cur_tail;
		cur_tail = next;
	}
}

bool snake_exists(Snake* snake, int x, int y, unsigned int radius) {
	if (!snake->next) {
		return false;
	}

	Snake* cur_tail = snake;
	if (abs(cur_tail->x - x) <= radius && abs(cur_tail->y - y) <= radius) {
		return true;
	}
	// this is safe becasue we always have a null_tail
	cur_tail = cur_tail->next;

	while (cur_tail->next) {
		if (cur_tail->x == x && cur_tail->y == y) {
			return true;
		}
		cur_tail = cur_tail->next;
	}
	return false;
}
