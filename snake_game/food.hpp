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
*
* Add methods to convert between enum and char
* 
* Change food_exists to return the type of food rather than bool
* Added None type food
*
* - Added guard bit to prevent this header file from being included twice
* - Added score_added to determine the point value of all the food types
* - Added Death type to act as an obstacles
*
* - Add method to deallocate memory of food
*
* - Add check to prevent food 
*   */

/*Copyright (c) 2022 Adeel Bhutta
*
* All rights reserved.
*
* Additional copyrights may follow
*/

#ifndef FOOD
#define FOOD
#include <ncurses.h>

//Two types of food
//Either Increase or Decrease length of snake
enum Type {Increase, Decrease, MegaIncrease, WegaDecrease, Death, None}; 

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
enum Type food_exists(Food* foods, int x, int y);
Food* create_food(int x, int y, enum Type type);
enum Type food_type(Food* foods, int x, int y);
Food* remove_eaten_food(Food* foods, int x, int y);
void draw_food(Food *food);
// Added Methods
enum Type type_from_char(char type); 
char char_from_type(enum Type type);
/**
 * Returns a random food type.
 */
enum Type random_food_type();
/**
 * Amount added or removed from the snake when it eats
 * the given food.
 * Ex. Returning a 1 means the snake will increase in size by 1
 */
int tails_added(enum Type type);
/**
 * Amount of score added based on the given food type.
 */
int score_added(enum Type type);
/**
 * Deallocates memory of the given food.
 */
void free_food(Food *food);
#endif
