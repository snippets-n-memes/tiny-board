#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define WWIDTH (COLS/4)
typedef enum {unassigned, inprogress, blocked, completed} Windows;

typedef struct {
  char *name;
  char *description; 
  int size;
  int pos;
  WINDOW *menu;
} Ticket;

void run();
WINDOW *newMenu(int x);
Ticket *newTicket(WINDOW *menu, char *title, char *desc);
void drawMenu(WINDOW *menu, char* title);
int drawTicket(Ticket *, int lineNumber);
void selectTicket(Ticket *);
void deselectTicket(Ticket *);
void clearTicketDesc(Ticket *);
