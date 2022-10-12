#include <ncurses.h>
#include <stdlib.h>

#define WWIDTH (COLS/4)
typedef enum {unassigned, inprogress, blocked, completed} Windows;

typedef struct {
  char *name;
  char *description; 
  WINDOW *menu;
} Ticket;

WINDOW *newMenu(int x);
void drawMenu(WINDOW *menu, char* title);
Ticket *initTicket(WINDOW *menu, char *title, char *desc);
