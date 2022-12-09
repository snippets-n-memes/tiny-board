#ifndef MAIN_H
#define MAIN_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ticket.h"

int run();
void generateTickets();
void initializeBoard();
void newTicketPrompt();

WINDOW *newMenu(int x);
void selectMenu(int key);
void drawMenu(WINDOW *menu, char *title);
void drawList(Windows status);
void illuminateMenu(int status);
void dimMenu(int status);

Ticket *newTicket(char *title, char *desc);
Ticket *removeTicket(Windows status, int id);
void selectTicket(int key);
void addTicket(Windows status, Ticket *);
int drawTicket(Ticket *, int lineNumber);

#endif
