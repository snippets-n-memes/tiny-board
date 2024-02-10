#include "main.h"

WINDOW *menus[4];
Ticket *tickets[4];
Ticket *ticketSelection;
Selecting level = ticket;

int key = 0;
int menuSelection = 0;
int scrollPosition[4];

char* title[4] = {"Unassigned", "In Progress", "Blocked", "Completed"};

void initializeBoard() {
  initscr();
  curs_set(0);
  refresh();
  noecho();
  cbreak();

  for(int i = 0; i < 4; i++) menus[i] = newMenu(i*WWIDTH);

  for(int i = 0; i < 4; i++) {
    drawMenu(menus[i], title[i]);
    keypad(menus[i], TRUE);
    scrollPosition[i] = 0;
    drawList(i);
    wrefresh(menus[i]);
  }

  if (tickets[unassigned] != NULL) {
    ticketSelection = tickets[unassigned];
    illuminateTicket(ticketSelection);
  }
}