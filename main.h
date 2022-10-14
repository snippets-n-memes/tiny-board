#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define WWIDTH (COLS/4)
typedef enum {unassigned, inprogress, blocked, completed, none} Windows;

typedef struct Ticket{
  int id;
  char *name;
  char *description; 
  int size;
  int pos;
  struct Ticket *next;
  Windows status;
} Ticket;

void run();
WINDOW *newMenu(int x);
Ticket *newTicket(char *title, char *desc);
void drawMenu(WINDOW *menu, char *title);
void drawList(Windows status);
void addTicket(Windows status, Ticket *);
Ticket *removeTicket(Windows status, int id);
int drawTicket(Ticket *, int lineNumber);
void selectTicket(Ticket *);
void deselectTicket(Ticket *);
void clearTicketDesc(Ticket *);
