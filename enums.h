#ifndef ENUMS_H
#define ENUMS_H

#include <ncurses.h>

#define WWIDTH (COLS/4)
typedef enum {
  unassigned = 0, 
  inprogress = 1, 
  blocked = 2, 
  completed = 3, 
  none = 4
} Windows;

typedef enum {menu, ticket} Selecting;

#include "ticket.h"

#endif
