#ifndef MAIN_H
#define MAIN_H

#include "ticket.h"
#include "menu.h"

int run();
void initializeBoard();
void newTicketPrompt();

WINDOW *newMenu(int x);
void selectMenu(int key);

void selectTicket(int key);

#endif
