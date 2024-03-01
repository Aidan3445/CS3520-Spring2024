/* key.cpp -------
 *
 * Filename: key.cpp
 * Description:
 * Author: Adeel Bhutta
 * Maintainer:
 * Created: Sun Sep 13 20:29:30 2022
 * Last-Updated: September 13 22:39 2022
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 * add wasd support
 *
 */

/* Copyright (c) 2022 Adeel Bhutta
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */

#include <ncurses.h>
#include "key.hpp"

int get_char()
{
  int ch = getch();
  if (ch == ERR)
  {
    return (NOCHAR);
  }
  switch (ch)
  {
  case KEY_LEFT:
  case 65:
  case 97:
    return LEFT;
    break;
  case KEY_RIGHT:
  case 68:
  case 100:
    return RIGHT;
    break;
  case KEY_UP:
  case 87:
  case 119:
    return UP;
    break;
  case KEY_DOWN:
  case 83:
  case 115:
    return DOWN;
    break;
  default:
    return (ch);
    break;
  }
}
