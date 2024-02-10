#ifndef MAIN_H
#define MAIN_H

#include "ticket.h"
#include "menu.h"
#include "text_field.h"

Ticket** run();
void initializeBoard();
void newTicketPrompt();
void deleteMenus();

WINDOW *newMenu(int x);
void selectMenu(int key);

void selectTicket(int key);

#endif
