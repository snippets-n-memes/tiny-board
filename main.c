#include <ncurses.h>

#define WWIDTH (COLS/4)
enum Windows{unassigned, inprogress, blocked, completed};

WINDOW * newMenu(int x);
void drawMenu(WINDOW * menu);

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

  for(int i = 0; i < 4; i++) {
    drawMenu(menu[i], title[i]);
    wgetch(menu[i]);
  }

  endwin();
  return(0);
}

WINDOW * newMenu(int x){
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
