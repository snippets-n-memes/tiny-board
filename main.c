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

  Ticket test1 = *newTicket(menu[0],"testing", "test tickets with a long description.");

  for(int i = 0; i < 4; i++) {
    drawMenu(menu[i], title[i]);
    wgetch(menu[i]);
  }

  drawTicket(&test1);

  endwin();
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
  int len = strlen(t.description);
  int y = 3;
  int menuWidth = WWIDTH - 6;

  wmove(t.menu,y,2);
  waddstr(t.menu,t.name);
  wmove(t.menu,++y,2);
  whline(t.menu, ACS_HLINE, WWIDTH - 5);

  for (int i = 0; i < len; i += WWIDTH - 6) {
    wmove(t.menu,++y,2);
    if (!i){
      wprintw(t.menu,"- %.*s", menuWidth, t.description + i);
    } else {
      wprintw(t.menu,"%.*s", menuWidth, t.description + i);
    }
  }

  wrefresh(t.menu);
  wgetch(t.menu);
}