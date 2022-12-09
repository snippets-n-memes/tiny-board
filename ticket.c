#include "ticket.h"

extern WINDOW *menus[];

void illuminateTicket(Ticket *ticket) {
  WINDOW *win = menus[ticket->status];
  int size = ticket->size;
  int y = ticket->pos-size-4;
  use_default_colors();
  start_color();
  init_pair(1,COLOR_GREEN,-1);
  wattrset(win, COLOR_PAIR(1));

  // top
  wmove(win, y, 1);
  waddch(win, ACS_ULCORNER);
  whline(win, ACS_HLINE, WWIDTH - 4);
  wmove(win, y, WWIDTH - 2);
  waddch(win, ACS_URCORNER);

  //sides
  wmove(win, ++y, WWIDTH - 2);
  wvline(win, ACS_VLINE, size+2);
  wmove(win, y, 1);
  wvline(win, ACS_VLINE, size+2);

  //bottom
  wmove(win, y+size+2, 1);
  waddch(win, ACS_LLCORNER);
  whline(win, ACS_HLINE, WWIDTH - 4);
  wmove(win, y+size+2, WWIDTH - 2);
  waddch(win, ACS_LRCORNER);

  wattrset(win, A_NORMAL);
  wrefresh(win);
}

void dimTicket(Ticket *ticket) {
  WINDOW *win = menus[ticket->status]; 
  int size = ticket->size;
  int y = ticket->pos-size-4;

  // top
  wmove(win, y, 1);
  waddch(win, ' ');
  whline(win, ' ', WWIDTH - 4);
  wmove(win, y, WWIDTH - 2);
  waddch(win, ' ');

  //sides
  wmove(win, ++y, WWIDTH - 2);
  wvline(win, ' ', size+2);
  wmove(win, y, 1);
  wvline(win, ' ', size+2);

  //bottom
  wmove(win, y+size+2, 1);
  waddch(win, ' ');
  whline(win, ' ', WWIDTH - 4);
  wmove(win, y+size+2, WWIDTH - 2);
  waddch(win, ' ');
  wrefresh(win);
}

void clearTicketDesc(Ticket *ticket) {
  WINDOW *win = menus[ticket->status];  
  int y = ticket->pos-ticket->size-2;
  for(int i=0; i < ticket->size; i++) {
    wmove(win,++y,2);
    whline(win, ' ', WWIDTH - 4);
  }

  wrefresh(win);
  wgetch(win);
}
