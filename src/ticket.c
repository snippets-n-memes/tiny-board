#include "ticket.h"

extern WINDOW *menus[];
extern Ticket *tickets[];

int nextId = 0;

int newId() { return ++nextId; }

Ticket *newTicket(char *title, char *desc) {
  Ticket* res = malloc(sizeof(Ticket));
  res->id = newId();
  res->name = title;
  res->description = desc;
  res->pos = LINES + 1;
  res->size = 1;
  res->next = NULL;
  res->status = none;
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

  return res;
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

int drawTicket(Ticket *ticket, int line){
  WINDOW *win = menus[ticket->status];
  int y = line;
  int menuWidth = WWIDTH - 6;
  int len = strlen(ticket->description);
  char* head = ticket->description;

  wmove(win,y,2);
  waddstr(win,ticket->name);
  wmove(win,++y,2);
  whline(win, ACS_HLINE, WWIDTH - 5);

  int i = 0;
  while (i < len && y < (LINES-1)) {
    // trim leading whitespace
    if ((head + i)[0] == ' ') {
      i++;
      continue;
    }

    // nextline
    wmove(win,++y,3);

    // lastline
    if (i + menuWidth > len) {
      wprintw(win,"%.*s", menuWidth, head + i);
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

      wprintw(win,"%.*s", indexOf, head + i);
      i += indexOf;
    } else {
      wprintw(win,"%.*s", menuWidth, head + i);
      i += menuWidth;
    }
  }

  return y + 2;
}

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

void generateTickets() {
  Ticket *test1 = newTicket("testing", "test tickets with a long description.");
  Ticket *test2 = newTicket("test chain", "test tickets adding an addtional ticket, with a long description.");
  Ticket *test3 = newTicket("test chain", "make decision about managing tickets as files, or by writing driver code in go and manage in memory");
  Ticket *test4 = newTicket("check spacing", "make sure there's not too much room between two tickets in the same menu");
  Ticket *test13 = newTicket("test chain", "make decision about managing tickets as files, or by writing driver code in go and manage in memory");
  Ticket *test14 = newTicket("check spacing", "make sure there's not too much room between two tickets in the same menu");
  Ticket *test15 = newTicket("check spacing", "make sure there's not too much room between two tickets in the same menu");

  addTicket(unassigned, test1);
  addTicket(unassigned, test2);
  addTicket(unassigned, test3);
  addTicket(unassigned, test13);
  addTicket(unassigned, test14);
  addTicket(unassigned, test15);
  addTicket(unassigned, test4);

  Ticket *test5 = newTicket("testing", "test tickets with a long description.");
  Ticket *test6 = newTicket("test chain", "test tickets adding an addtional ticket, with a long description.");
  Ticket *test7 = newTicket("test chain", "make decision about managing tickets as files, or by writing driver code in go and manage in memory");
  Ticket *test8 = newTicket("check spacing", "make sure there's not too much room between two tickets in the same menu");

  addTicket(inprogress, test5);
  addTicket(inprogress, test6);
  addTicket(blocked, test7);
  addTicket(completed, test8);
}

<<<<<<< HEAD
Ticket **getAllTickets() {
=======
Ticket **getTickets(Windows status) {
>>>>>>> 41799db (cleanup)
  return tickets;
}

Ticket *getTickets(Windows status) {
  return tickets[status];
}