/*food.hpp -------
*
* Filename: food.hpp
* Description:
* Author: Adeel Bhutta
* Maintainer:
* Created: Sat Sep 12 13:21:55 2022
* Last-Updated: September 12 16:01 2022
*
*/

/* Commentary:
*
*
*
*/

/* Change log:
*
* - Added two more food types: MegaIncrease (with the symbol as 'M') to increase snake size by a large amount
*   and added WegaDecrease (with the symbol as 'W') to decrease snake size by a large amount
*/

/*Copyright (c) 2022 Adeel Bhutta
*
* All rights reserved.
*
* Additional copyrights may follow
*/

#include <ncurses.h>

//Two types of food
//Either Increase or Decrease length of snake
enum Type {Increase, Decrease, MegaIncrease, WegaDecrease}; 

//Structure to hold properties of food
struct Food {
  int x;
  int y;
  char type;
  struct Food* next;
};

typedef struct Food Food; 

//Function prototypes 
void add_new_food(Food* foods, Food* new_food);
bool food_exists(Food* foods, int x, int y);
Food* create_food(int x, int y, enum Type type);
enum Type food_type(Food* foods, int x, int y);
Food* remove_eaten_food(Food* foods, int x, int y);
void draw_food(Food *food);
// Added Methods
Type random_food_type();