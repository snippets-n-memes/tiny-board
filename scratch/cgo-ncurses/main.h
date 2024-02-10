#ifndef MAIN_H
#define MAIN_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WWIDTH (COLS/4)

typedef enum {
  unassigned = 0, 
  inprogress = 1, 
  blocked = 2, 
  completed = 3, 
  none = 4
} Windows;

typedef enum {menu, ticket} Selecting;

typedef struct Ticket Ticket;

struct Ticket{
  int id;
  char *name;
  char *description; 
  int size;
  int pos;
  struct Ticket *next;
  Windows status;
};

void initializeBoard();
void selectMenu(int key);

void selectTicket(int key);

Ticket *newTicket(char *title, char *desc);
Ticket *removeTicket(Windows status, int id);
Ticket **getAllTickets();
Ticket *getTickets(Windows status);
void addTicket(Windows status, Ticket *);
int drawTicket(Ticket *, int lineNumber);
void illuminateTicket(Ticket *);
void dimTicket(Ticket *);
void clearTicketDesc(Ticket *);

WINDOW *newMenu(int x);
void drawMenu(WINDOW *menu, char *title);
void drawList(Windows status);
void illuminateMenu(int status);
void dimMenu(int status);


#endif
