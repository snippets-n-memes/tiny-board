#include "main.h"

extern WINDOW *menus[];
extern Ticket *tickets[];
extern int scrollPosition[];

WINDOW *newMenu(int x){
  return newwin(LINES,WWIDTH,0,x);
}

void drawList(Windows status) {
  int y = 4;
  Ticket *i = tickets[status];
  for(int k = scrollPosition[status]; k > 0; k--) {
    i->pos = -1;
    if(i->next != NULL) i = i->next;
  }
  
  while(i != NULL && y < LINES - 1) {
    i->pos = drawTicket(i, y);
    y = i->pos + 1;
    i=i->next;
  }

  for (;i != NULL; i=i->next) i->pos = LINES + 1;
}

void drawMenu(WINDOW *menu, char* title) {
  //border
  box(menu,0,0);
  wmove(menu,1,1);

  //title
  waddstr(menu,title);
  wmove(menu,2,1);

  //underline
  whline(menu, ACS_HLINE, WWIDTH-2);

  wrefresh(menu);
}

void illuminateMenu(int status) {
  WINDOW*win = menus[status];
  use_default_colors();
  start_color();
  init_pair(1,COLOR_GREEN,-1);
  wattrset(win, COLOR_PAIR(1));
  box(win, 0, 0);
  wattrset(win, A_NORMAL);
  wrefresh(menus[status]);
}

void dimMenu(int status) {
  WINDOW *win = menus[status];
  box(win, 0, 0);
  wrefresh(menus[status]);
}
