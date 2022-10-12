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
Ticket *newTicket(WINDOW *menu, char *title, char *desc);
void drawMenu(WINDOW *menu, char* title);
void drawTicket(Ticket *);
