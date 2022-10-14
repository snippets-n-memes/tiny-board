#include "main.h"

#ifdef CTEST
int main() {
  run();
  return(0);
}
#endif

WINDOW *menu[4]; 
Ticket *tickets[4];
int nextId = 0;

void run(){
  initscr();
  curs_set(0);
  addstr("This is the standard screen\n");
  move(1,0);
  printw("WWIDTH = %d", WWIDTH);
  refresh();
  getch();

  char* title[4] = {"Unassigned", "In Progress", "Blocked", "Completed"};

  for(int i = 0; i < 4; i++) menu[i] = newMenu(i*WWIDTH);

  // Ticket test1 = *
  newTicket("testing", "test tickets with a long description.");
  // Ticket test2 = *
  newTicket("test chain", "test tickets adding an addtional ticket, with a long description.");
  // Ticket test3 = *
  newTicket("test chain", "make decision about managing tickets as files, or by writing driver code in go and manage in memory");
  Ticket test4 = *
  newTicket("check spacing", "make sure there's not too much room between two tickets in the same menu");

  // addTicket(unassigned, &test1);
  // addTicket(unassigned, &test2);
  // addTicket(unassigned, &test3);
  // addTicket(unassigned, &test4);

  for(int i = 0; i < 4; i++) {
    drawMenu(menu[i], title[i]);
    // wgetch(menu[i]);
  }

  drawList(unassigned);
  removeTicket(unassigned,test4.id);
  wclear(menu[unassigned]);
  drawMenu(menu[unassigned], title[unassigned]);
  drawList(unassigned);
  wrefresh(menu[unassigned]);
  wgetch(menu[unassigned]);
  
  // test1.pos = drawTicket(&test1, 4);
  // test2.pos = drawTicket(&test2, test1.pos+1);
  // test3.pos = drawTicket(&test3, 4);
  // drawTicket(&test4, test3.pos+1);

  // selectTicket(&test3);
  // deselectTicket(&test3);
  // selectTicket(&test1);
  // selectTicket(&test2);

  endwin();
}

WINDOW *newMenu(int x){
  return newwin(LINES,WWIDTH,0,x);
}

int newId() { return ++nextId;}

Ticket *newTicket(char *title, char *desc) {
  Ticket* res = malloc(sizeof(Ticket));
  res->id = newId();
  res->name = title;
  res->description = desc;
  res->pos = 3;
  res->size = 1;
  res->next = NULL;
  int len = strlen(desc);

  int menuWidth = WWIDTH - 6;
  int i = 0;
  while (i < len) {
    // trim leading whitespace
    if ((desc + i)[0] == ' ') {
      i++;
      continue;
    }

    // lastline
    if (i + menuWidth > len) {
      break;
    }

    // find last whitespace in slice
    if ((desc+i)[menuWidth-1] != ' ' && (desc+i)[menuWidth] != ' ') {
      int indexOf = 0;
      for (int j = indexOf; j < menuWidth; j++) {
        if ((desc+i)[j] == ' ') {
          indexOf = j;
        }
      }

      i += indexOf;
    } else {
      i += menuWidth;
    }
    res->size++;
  } 

  addTicket(unassigned, res);
  return res;
}

void drawList(Windows status) {
  int y = 4;
  Ticket *i = tickets[status];
  while(i != NULL) {
    i->pos = drawTicket(i, y);
    y = i->pos + 1;
    i=i->next;
  }
}

void addTicket(Windows status, Ticket *ticket) {
  ticket->status = status;
  if (tickets[status] == NULL) {
    tickets[status] = ticket;
  } else {
    Ticket *i = tickets[status];
    while(i->next != NULL) i = i->next;
    i->next = ticket;
  }
}

Ticket *removeTicket(Windows status, int id) {
  Ticket *i = tickets[status];
  if (i->id == id) {
    tickets[status] = i->next;
    i->next = NULL;
    i->status = none;
    return i;
  }

  while(i->next != NULL && i->next->id != id) i=i->next;

  if (i->next->id == id) {
    Ticket *temp = i->next;
    if(temp->next != NULL) {
      i->next = temp->next;
      temp->next = NULL;
    } else {
      i->next = NULL;
    }
    temp->status = none;
    return temp;
  }
  return NULL;
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

  wmove(menu[t.status],y,2);
  waddstr(menu[t.status],t.name);
  wmove(menu[t.status],++y,2);
  whline(menu[t.status], ACS_HLINE, WWIDTH - 5);

  int i = 0;
  while (i < len) {
    // trim leading whitespace
    if ((head + i)[0] == ' ') {
      i++;
      continue;
    }

    // nextline
    wmove(menu[t.status],++y,3);

    // lastline
    if (i + menuWidth > len) {
      wprintw(menu[t.status],"%.*s", menuWidth, head + i);
      break;
    }

    // find last whitespace in slice
    if ((head+i)[menuWidth-1] != ' ' && (head+i)[menuWidth] != ' ') {
      int indexOf = 0;
      for (int j = indexOf; j < menuWidth; j++) {
        if ((head+i)[j] == ' ') {
          indexOf = j;
        }
      }

      wprintw(menu[t.status],"%.*s", indexOf, head + i);
      i += indexOf;
    } else {
      wprintw(menu[t.status],"%.*s", menuWidth, head + i);
      i += menuWidth;
    }
  }

  wrefresh(menu[t.status]);
  wgetch(menu[t.status]);
  return y + 2;
}

void selectTicket(Ticket *ticket) {
  WINDOW *win = menu[ticket->status];
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
  wgetch(win);
}

void deselectTicket(Ticket *ticket) {
  WINDOW *win = menu[ticket->status]; 
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
  wgetch(win);

}

void clearTicketDesc(Ticket *ticket) {
  WINDOW *win = menu[ticket->status];  
  int y = ticket->pos-ticket->size-2;
  for(int i=0; i < ticket->size; i++) {
    wmove(win,++y,2);
    whline(win, ' ', WWIDTH - 4);
  }

  wrefresh(win);
  wgetch(win);
}