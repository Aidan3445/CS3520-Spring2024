/* game_window.cpp -------
 *
 * Filename: game_window.cpp
 * Description:
 * Author: Adeel Bhutta
 * Maintainer:
 * Created: Tue Sep  6 14:10:06 2022
 * Last-Updated: June 4 11:00 2022
 * Keywords:
 * Compatibility:
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 * added pause menu method
 *
 * added scoring method
 *
 * add difficulty to start menu
 *
 *
 * COLORS!!!!!
 */

/* Copyright (c) 2022 Adeel Bhutta
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

/* Code: */

#include <cstdlib>
#include <ncurses.h>
#include "game_window.hpp"
#include "food.hpp"

gamewindow_t *init_GameWindow(int upper_left_x, int upper_left_y, int width, int height)
{
    gamewindow_t *g;
    g = (gamewindow_t *) malloc(sizeof(gamewindow_t));
    g->upper_left_x = upper_left_x;
    g->upper_left_y = upper_left_y;
    g->width = width;
    g->height = height;
    g->draw_char = '*';
    return (g);
}

void draw_Gamewindow(gamewindow_t *r)
{
    int row_counter, column_counter;

    attron(COLOR_PAIR(4));
    // Draw Top of room
    for (row_counter = r->upper_left_x;
            row_counter <= (r->upper_left_x + r->width);
            row_counter++) {
        mvprintw(r->upper_left_y, row_counter, "%c", r->draw_char);
    }

    // Draw left side of room
    for (column_counter = r->upper_left_y;
            column_counter <= (r->upper_left_y + r->height);
            column_counter++) {
        mvprintw(column_counter, r->upper_left_x, "%c", r->draw_char);
    }

    // Draw right side of room
    for (column_counter = r->upper_left_y;
            column_counter <= (r->upper_left_y + r->height);
            column_counter++) {
        mvprintw(column_counter, (r->upper_left_x + r->width), "%c", r->draw_char);
    }

    // Draw Bottom of room
    for (row_counter = r->upper_left_x;
            row_counter <= (r->upper_left_x + r->width);
            row_counter++) {
        mvprintw(r->upper_left_y + r->height, row_counter, "%c", r->draw_char);
    }
    attroff(COLOR_PAIR(4));
}

gamewindow_t *changeGameWindow(int upper_left_x, int upper_left_y, int width, int height, gamewindow_t *r)
{
    r->upper_left_x = upper_left_x;
    r->upper_left_y = upper_left_y;

    if (width < 10)
        r->width = 10;
    else
        r->width = width;

    if (height < 10)
        r->height = 10;
    else
        r->height = height;

    return (r);
}

void undraw_Gamewindow(gamewindow_t *r)
{
    int row_counter, column_counter;

    // Undraw Top of room
    for (row_counter = r->upper_left_x;
            row_counter <= (r->upper_left_x + r->width);
            row_counter++) {
        mvprintw(r->upper_left_y, row_counter, " ");
    }

    // Undraw left side of room
    for (column_counter = r->upper_left_y;
            column_counter<=(r->upper_left_y + r->height);
            column_counter++) {
        mvprintw(column_counter, r->upper_left_x, " ");
    }

    // Undraw right side of room
    for (column_counter = r->upper_left_y;
            column_counter <= (r->upper_left_y + r->height);
            column_counter++) {
        mvprintw(column_counter, (r->upper_left_x + r->width), " ");
    }

    // Undraw Bottom of room
    for (row_counter = r->upper_left_x;
            row_counter <= (r->upper_left_x + r->width);
            row_counter++) {
        mvprintw(r->upper_left_y + r->height, row_counter, " ");
    }
}
/* room.c ends here */

// Added Methods

void draw_pause_menu(int x_offset, int y_offset, int width, int height)
{
    const char *lines[17] = {
        "+---------------+",
        "|  Game Paused: |",
        "| 'p' to resume |",
        "|  'q' to quit  |",
        "+---------------+",
        NULL // terminator
    };

    attron(COLOR_PAIR(5));
    for (int i = 0; lines[i] != NULL; i++) {
        mvprintw(y_offset + (height / 2) + i, 
                x_offset + (width / 2) - 8, lines[i]);
    }
    attroff(COLOR_PAIR(5));
}

void draw_start_menu(int x_offset, int y_offset, int width, int height, int difficulty)
{
    const char *lines[17] = {
        "+---------------------+",
        "|  Press s to start!  |",
        "|  <--           -->  |",
        "+---------------------+",
        "+---------------------+",
        "|  How to Play:       |",
        "|  - Use arrow keys   |",
        "|    or wsad to move  |",
        "|  - Press p to pause |",
        "|  - Press q to quit  |",
        "+---------------------+",
        NULL // terminator
    };
    // Subtracts (5, 12) to account for centering the start menu
    // by subtracting from the cursor half the size of the menu
    attron(COLOR_PAIR(5));
    for (int i = 0; lines[i] != NULL; i++) {
        mvprintw(y_offset + (height / 2) + i - 5, 
                x_offset + (width / 2) - 12, lines[i]);
    }
    attroff(COLOR_PAIR(5));

    // print the difficulty
    // 0 - easy, 1 - hard, 2 - advanced
    // 3 - expert, 4 - insane    i
    const char *diffs[3] = {
        "    Easy", "    Hard", "  Advanced"
    };
    if (difficulty < 0) {
        difficulty = 0;
    } else if (difficulty > 2) {
        difficulty = 2;
    }

    switch(difficulty) {
        case 0:
            init_pair(7, COLOR_BLUE, COLOR_CYAN); // easy - blue
            break;
        case 1:
            init_pair(7, COLOR_MAGENTA, COLOR_CYAN); // hard - magenta
            break;
        case 2:
            init_pair(7, COLOR_RED, COLOR_CYAN); // advanced - red
            break;
        default:
            throw "Invalid difficulty";
    }

    attron(COLOR_PAIR(7));
    mvprintw(y_offset + (height / 2) - 3, x_offset + (width / 2) - 6, diffs[difficulty]); 
    attroff(COLOR_PAIR(7));
}

// Assumes top_three is an array of at least 3 ints
void draw_score(int score, int* top_three, int x_offset, int y_offset, int width, int height) {
    const char *lines[18] = {
        "+---------------------+ ",
        "|     Scoreboard:     | ",
        "| ------------------- | ",
        "|                     | ",
        "|                     | ",
        "|                     | ",
        "|                     | ",
        "+---------------------+ ",
        "                        ",
        "+---------------------+ ",
        "|       Scoring:      | ",
        "| ------------------- | ",
        "|                     | ",
        "|                     | ",
        "|                     | ",
        "|                     | ",
        "+---------------------+ ",
        NULL // terminator
    };
    // Subtracts (4, 12) to account for centering the start menu
    // by subtracting from the cursor half the size of the menu
    attron(COLOR_PAIR(5));
    for (int i = 0; lines[i] != NULL; i++) {
        mvprintw(y_offset + i, 
                x_offset + width + 2, lines[i]);
    }
    // print the score
    mvprintw(y_offset + 3, x_offset + width + 8, "Score: %d", score);
    // prints top 3
    mvprintw(y_offset + 4, x_offset + width + 7, "High 1: %d", top_three[0]);
    mvprintw(y_offset + 5, x_offset + width + 7, "High 2: %d", top_three[1]);
    mvprintw(y_offset + 6, x_offset + width + 7, "High 3: %d", top_three[2]);
    // todo: print the other scores

    for (int i = 0; i < 4; i++) {
        enum Type foodType = (enum Type) i;
        char typeChar = char_from_type(foodType);
        int typeScore = score_added(foodType);

        mvprintw(y_offset + 12 + i, x_offset + width + 9, 
                "%c: %s%d pts.", typeChar, typeScore > 0 ? " " : "", typeScore);
    }
    attroff(COLOR_PAIR(5));
}

void draw_dead(int lives_remaining, int x_offset, int y_offset, int width, int height)
{
    const char *lines[17] = {
        "+----------------+",
        "|    You Died!   |",
        "| -------------- |",
        "|    Lives:      |",
        "| -------------- |",
        "| 'r' to respawn |",
        "|  'q' to quit   |",
        "+----------------+",
        NULL // terminator
    };

    attron(COLOR_PAIR(6));
    for (int i = 0; lines[i] != NULL; i++) {
        mvprintw(y_offset + (height / 2) + i, 
                x_offset + (width / 2) - 8, lines[i]);
    }

    mvprintw(y_offset + (height / 2) + 3, 
            x_offset + (width / 2) + 4, "%d", lives_remaining);

    if (lives_remaining <= 0) {
        mvprintw(y_offset + (height / 2) + 1, 
                x_offset + (width / 2) - 3, "GAME OVER");
        mvprintw(y_offset + (height / 2) + 5, 
                x_offset + (width / 2) + 1, "restart");
    }
    attroff(COLOR_PAIR(6));
}

