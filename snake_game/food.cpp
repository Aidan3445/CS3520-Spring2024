/*food.cpp -------
*
* Filename: food.cpp
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
* add handling for 2 new food types
*
*/

/*Copyright (c) 2022 Adeel Bhutta
*
* All rights reserved.
*
* Additional copyrights may follow
*/

#include <cstdlib>
#include <ncurses.h>
#include <cstdbool>
#include "food.hpp"


//Create new food
Food* create_food(int x, int y, enum Type type){
    Food* new_food = (Food*)malloc(sizeof(Food));
     
    new_food->x = x;
    new_food->y = y;
    new_food->type = char_from_type(type);
    new_food->next = NULL;

    return new_food;
}

//Check if food exists at coordinates
enum Type food_exists(Food* foods, int x, int y){
    Food* temp = foods;
    while(temp){
        if(temp->x == x && temp->y == y)
            return type_from_char(temp->type);
        temp = temp->next;
    }
    return None;
}

//Add new food to end of food list
void add_new_food(Food* foods, Food* new_food){
    Food* temp = foods;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = new_food;
}

//Convert enum to char
char char_from_type(enum Type type) {
    switch(type) {
        case Increase:
            return 'O';
        case Decrease:
            return 'X';
        case MegaIncrease:
            return 'M';
        case WegaDecrease:
            return 'W';
        default:
            // indicates an error food state
            return '?';
    }
}

//Convert char to enum
enum Type type_from_char(char type) {
    switch(type) {
        case 'O':
            return Increase;
        case 'X':
            return Decrease;
        case 'M':
            return MegaIncrease;
        case 'W':
            return WegaDecrease;
        default:
            // indicates an error food state
            return None;
    }
}


enum Type food_type(Food* foods, int x, int y){
    //Implement the code to return the type of the food 
    //present at position (x, y)	

    Food* temp = foods;
    while(temp){
        if(temp->x == x && temp->y == y)
            return type_from_char(temp->type);
        temp = temp->next;
    }

    return None;
}
Food* remove_eaten_food(Food* foods, int x, int y){
	//Implement the code to remove food at position (x,y).
	//Create a new linked list of type Food containing only the
	//needed food and return this new list

    // if we reach the end of the list, return NULL
    if(!foods) return NULL;

    // if the current food is eaten, then remove it and recurse
    if (foods->x == x && foods->y == y) {
        Food* temp = foods->next;
        free(foods);
        return temp;
    }

    // if the current food is not eaten, then keep it and recurse
    foods->next = remove_eaten_food(foods->next, x, y);
    return foods;
}

// Display all the food
void draw_food (Food *foods)
{   Food* temp = foods;
    while(temp) {
        mvprintw(temp->y, temp->x, "%c", temp->type);
        temp = temp->next;
    }
}

enum Type random_food_type() {
    // Selects a random type by using the fact that enums go from 
    // 0 to the number of states - 1. 
    // So this will return one of the first 4 states in Type 
    // (which are all the valid states)
    return (Type)(rand() % 4);
}

int tails_added(enum Type type) {
    switch (type) {
        case Increase:
            return 1;
        case Decrease:
            return -1;
        case MegaIncrease:
            return 3;
        case WegaDecrease:
            return -3;
        default:
            return 0;
    }
}

int score_added(enum Type type) {
    switch (type) {
        case Increase:
            return 20;
        case Decrease:
            return -10;
        case MegaIncrease:
            return 60;
        case WegaDecrease:
            return -30;
        default:
            return 0;
    }
}