#include "main.h"

int main(){
  initscr();
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

  Ticket test1 = *newTicket(menu[0],"testing", "test tickets with a long description.");

  for(int i = 0; i < 4; i++) {
    drawMenu(menu[i], title[i]);
    wgetch(menu[i]);
  }

  drawTicket(&test1);

  endwin();
  return(0);
}

WINDOW *newMenu(int x){
  return newwin(LINES,WWIDTH,0,x);
}

Ticket* newTicket(WINDOW *menu, char *title, char *desc) {
  Ticket* res = malloc(sizeof(Ticket));
  res->name=title;
  res->description=desc;
  res->menu=menu;
  return res;
}

void drawMenu(WINDOW * menu, char* title) {
  //border
  box(menu,0,0);
  wmove(menu,1,1);

  //title
  waddstr(menu,title);
  wmove(menu,2,1);

  //underline
  whline(menu, ACS_HLINE, WWIDTH-2);

  //draw window
  wrefresh(menu);
}

void drawTicket(Ticket *ticket){
  Ticket t = *ticket;
  wmove(t.menu,3,2);
  waddstr(t.menu,t.name);
  wmove(t.menu,4,2);
  whline(t.menu, ACS_HLINE, WWIDTH - 5);
  wmove(t.menu,5,2);
  wprintw(t.menu,"- %.*s", WWIDTH - 6, t.description);
  wmove(t.menu,6,2);
  wprintw(t.menu,"%.*s", WWIDTH - 6, t.description+WWIDTH-6);
  wrefresh(t.menu);
  wgetch(t.menu);
}