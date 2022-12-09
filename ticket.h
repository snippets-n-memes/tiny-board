#ifndef TICKET_H
#define TICKET_H

typedef struct Ticket Ticket;

#include "enums.h"
#include <ncurses.h>

struct Ticket{
  int id;
  char *name;
  char *description; 
  int size;
  int pos;
  struct Ticket *next;
  Windows status;
};

void illuminateTicket(Ticket *);
void dimTicket(Ticket *);
void clearTicketDesc(Ticket *);

#endif
