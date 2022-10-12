#include "main.h"

int main(){
  initscr();
  addstr("This is the standard screen\n");
  refresh();
  getch();

  WINDOW *menu[4]; 
  char* title[4] = {"Unassigned", "In Progress", "Blocked", "Completed"};

  menu[unassigned] = newMenu(0);
  menu[inprogress] = newMenu(WWIDTH);
  menu[blocked] = newMenu(2*WWIDTH);
  menu[completed] = newMenu(3*WWIDTH);

  Ticket test1 = *initTicket(menu[0],"testing", "test tickets with a long description.");

  for(int i = 0; i < 4; i++) {
    drawMenu(menu[i], title[i]);
    wgetch(menu[i]);
  }

  wmove(test1.menu,3,2);
  waddstr(test1.menu,test1.name);
  wmove(test1.menu,4,2);
  whline(test1.menu, ACS_HLINE, WWIDTH - 5);
  wmove(test1.menu,5,2);
  wprintw(test1.menu,"- %.*s", WWIDTH - 6, test1.description);
  wmove(test1.menu,6,2);
  wprintw(test1.menu,"%.*s", WWIDTH - 6, test1.description+WWIDTH-6);
  wrefresh(test1.menu);
  wgetch(test1.menu);

  endwin();
  return(0);
}

WINDOW *newMenu(int x){
  return newwin(LINES,WWIDTH,0,x);
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

Ticket* initTicket(WINDOW *menu, char *title, char *desc) {
  Ticket* res = malloc(sizeof(Ticket));
  res->name=title;
  res->description=desc;
  res->menu=menu;
  return res;
}