#ifndef MAIN_H
#define MAIN_H

#include "ticket.h"
#include "menu.h"
#include "text_field.h"

int run();
void initializeBoard();
void newTicketPrompt();
void deleteMenus();
Ticket** getMenuLists();

WINDOW *newMenu(int x);
void selectMenu(int key);

void selectTicket(int key);

#endif
