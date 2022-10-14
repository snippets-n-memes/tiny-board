#include "main.h"

#ifdef CTEST
int main() {
  run();
  return(0);
}
#endif

void run(){
  initscr();
  curs_set(0);
  addstr("This is the standard screen\n");
  refresh();
  getch();

  WINDOW *menu[4]; 
  char* title[4] = {"Unassigned", "In Progress", "Blocked", "Completed"};

  // menu[unassigned] = newMenu(0);
  // menu[inprogress] = newMenu(WWIDTH);
  // menu[blocked] = newMenu(2*WWIDTH);
  // menu[completed] = newMenu(3*WWIDTH);
  for(int i = 0; i < 4; i++) menu[i] = newMenu(i*WWIDTH);

  Ticket test1 = *newTicket(menu[unassigned],"testing", "test tickets with a long description.");
  Ticket test2 = *newTicket(menu[unassigned],"test chain", "test tickets adding an addtional ticket, with a long description.");
  Ticket test3 = *newTicket(menu[unassigned],"test chain", "overwrite... adding an addtional ticket, with a long description.");
  Ticket test4 = *newTicket(menu[inprogress],"test chain", "make decision about managing tickets as files, or by writing driver code in go and manage in memory");

  for(int i = 0; i < 4; i++) {
    drawMenu(menu[i], title[i]);
    // wgetch(menu[i]);
  }
  
  test1.pos = drawTicket(&test1, 4);
  test2.pos = drawTicket(&test2, test1.pos+2);
  test3.pos = drawTicket(&test3, test1.pos+2);
  test4.pos = drawTicket(&test4, 4);

  selectTicket(&test4);
  deselectTicket(&test4);
  selectTicket(&test3);
  selectTicket(&test1);

  endwin();
}

WINDOW *newMenu(int x){
  return newwin(LINES,WWIDTH,0,x);
}

Ticket *newTicket(WINDOW *menu, char *title, char *desc) {
  Ticket* res = malloc(sizeof(Ticket));
  res->name=title;
  res->description=desc;
  res->menu=menu;
  res->pos=3;
  res->size = 0;
  int len = strlen(desc);
  for (int i = 0; i < len; i += WWIDTH - 6) {
    res->size++;
  }
  return res;
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

int drawTicket(Ticket *ticket, int line){
  Ticket t = *ticket;
  int y = line;
  int menuWidth = WWIDTH - 6;
  int len = strlen(t.description);
  char* head = t.description;

  wmove(t.menu,y,2);
  waddstr(t.menu,t.name);
  wmove(t.menu,++y,2);
  whline(t.menu, ACS_HLINE, WWIDTH - 5);

  for (int i = 0; i < len; i+= menuWidth) {
    wmove(t.menu,++y,3);
    if ((head + i)[0] == ' ') i++;
    if ((head + i)[menuWidth] != ' ' &&)
    wprintw(t.menu,"%.*s", menuWidth, head + i);
  }

  wrefresh(t.menu);
  wgetch(t.menu);
  return y + 2;
}

void selectTicket(Ticket *ticket) {
  Ticket t = *ticket;
  int y = t.pos-t.size-4;
  use_default_colors();
  start_color();
  init_pair(1,COLOR_GREEN,-1);
  wattrset(t.menu, COLOR_PAIR(1));

  // top
  wmove(t.menu, y, 1);
  waddch(t.menu, ACS_ULCORNER);
  whline(t.menu, ACS_HLINE, WWIDTH - 4);
  wmove(t.menu, y, WWIDTH - 2);
  waddch(t.menu, ACS_URCORNER);

  //sides
  wmove(t.menu, ++y, WWIDTH - 2);
  wvline(t.menu, ACS_VLINE, t.size+2);
  wmove(t.menu, y, 1);
  wvline(t.menu, ACS_VLINE, t.size+2);

  //bottom
  wmove(t.menu, y+t.size+2, 1);
  waddch(t.menu, ACS_LLCORNER);
  whline(t.menu, ACS_HLINE, WWIDTH - 4);
  wmove(t.menu, y+t.size+2, WWIDTH - 2);
  waddch(t.menu, ACS_LRCORNER);

  wattrset(t.menu, A_NORMAL);

  wrefresh(t.menu);
  wgetch(t.menu);
}

void deselectTicket(Ticket *ticket) {
  Ticket t = *ticket;
  int y = t.pos-t.size-4;

  // top
  wmove(t.menu, y, 1);
  waddch(t.menu, ' ');
  whline(t.menu, ' ', WWIDTH - 4);
  wmove(t.menu, y, WWIDTH - 2);
  waddch(t.menu, ' ');

  //sides
  wmove(t.menu, ++y, WWIDTH - 2);
  wvline(t.menu, ' ', t.size+2);
  wmove(t.menu, y, 1);
  wvline(t.menu, ' ', t.size+2);

  //bottom
  wmove(t.menu, y+t.size+2, 1);
  waddch(t.menu, ' ');
  whline(t.menu, ' ', WWIDTH - 4);
  wmove(t.menu, y+t.size+2, WWIDTH - 2);
  waddch(t.menu, ' ');

  wrefresh(t.menu);
  wgetch(t.menu);

}

void clearTicketDesc(Ticket *ticket) {
  Ticket t = *ticket;
  int y = t.pos-t.size-2;
  for(int i=0; i < t.size; i++) {
    wmove(t.menu,++y,2);
    whline(t.menu, ' ', WWIDTH - 4);
  }

  wrefresh(t.menu);
  wgetch(t.menu);
}