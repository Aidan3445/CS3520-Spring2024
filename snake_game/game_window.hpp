/* game_windows.hpp ---------
 *
 * Filename: game_window.hpp
 * Description:
 * Author: Adeel Bhutta
 * Maintainer:
 * Created: Tue Sep  6 14:10:53 2022
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
 * add method to draw pause menu on screen
 * add method to draw start menu on screen
 * add method to draw score
 * add death screen
 */

/* Copyright (c) 2022 Adeel Bhutta
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

/* Code: */

#define WELL_WIDTH 50
#define WELL_HEIGHT 25

struct gamewindow_t
{
  int upper_left_x;
  int upper_left_y;
  int width;
  int height;
  char draw_char;
  char color[3];
};

typedef struct gamewindow_t gamewindow_t;

gamewindow_t *init_GameWindow(int, int, int, int);
gamewindow_t *changeGameWindow(int upper_left_x, int upper_left_y, 
        int width, int height, gamewindow_t *);

void undraw_Gamewindow(gamewindow_t *);
void draw_Gamewindow(gamewindow_t *);
// Added Methods
void draw_pause_menu(int x_offset, int y_offset, int width, int height);
void draw_start_menu(int x_offset, int y_offset, int width, int height, int difficulty);
void draw_score(int score, int x_offset, int y_offset, int width, int height);
void draw_dead(int lives_remaining, int x_offset, int y_offset, int width, int height);
