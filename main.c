#include "main.h"

WINDOW *menus[4]; 
Ticket *tickets[4];
Ticket *ticketSelection;
Selecting level = ticket;

int key = 0;
int nextId = 0;
int menuSelection = 0;
int scrollPosition[4];

char* title[4] = {"Unassigned", "In Progress", "Blocked", "Completed"};

#ifdef CTEST
int main() {
  initializeBoard();
  while(run());
  return 0;
}
#endif

void initializeBoard() {
  initscr();
  curs_set(0);
  refresh();
  noecho();

#ifdef DEBUG
  addstr("This is the standard screen\n");
  move(1,0);
  printw("WWIDTH = %d", WWIDTH);
  move(2,0);
  printw("LINES = %d", LINES);
  refresh();
  getch();
#endif

  for(int i = 0; i < 4; i++) menus[i] = newMenu(i*WWIDTH);

#ifdef CTEST
  generateTickets();
#endif

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

// idea: return the board as a list of tickets for golang to unmarshall 
int run() {
  key = wgetch(menus[menuSelection]);

  switch (key) {
    case 'q':
    case 'Q':
      endwin();
      return 0;
    case 'n':
      newTicketPrompt();
      break;
    case 10: // enter
      if (level != ticket) {
        level = ticket;
        ticketSelection = tickets[menuSelection];
        dimMenu(menuSelection);
        if (ticketSelection != NULL) illuminateTicket(ticketSelection);
      }
      break;
    case 27: // esc
      if (level != menu) {
        level = menu;
        if (ticketSelection != NULL) dimTicket(ticketSelection);
        illuminateMenu(menuSelection);
      }
      break;
    default:
      if (level == menu) 
        selectMenu(key);
      else if (level == ticket) 
        selectTicket(key);
      break;
  }
  return 1;
}

void newTicketPrompt(){
  int width = (COLS/2) - 1;

#ifdef DEBUG
  WINDOW *debug = newwin(6,(COLS/2) + 4,(3*LINES/4),(COLS/4)-2);
#endif

  WINDOW *border = newwin(LINES/2,(COLS/2)+4,LINES/4,(COLS/4)-2);
  box(border,0,0);
  wrefresh(border);

  WINDOW *prompt = newwin((LINES/2)-4,(COLS/2),(LINES/4)+2,(COLS/4));
  wmove(prompt,0,1);
  wprintw(prompt,"Ticket Name: ");
  wmove(prompt,2,1);
  wprintw(prompt,"Description: ");
  wrefresh(prompt);

  WINDOW *name = newwin(1, (COLS/2)-17, (LINES/4)+2,(COLS/4)+13);
  int nameWidth = (COLS/2)-17;
  WINDOW *activeWindow = name;
  char *nameBuffer = malloc(sizeof(char) * 100);
  wrefresh(activeWindow);
  curs_set(1);
  keypad(activeWindow, TRUE);
  int i = 0, x = 0, y = 0, chars = 0, index = 0, offset = 0;
  while(i != 10){
    getyx(activeWindow, y, x);
    wrefresh(activeWindow);
    i = wgetch(activeWindow);

    switch (i){
      case 127:
      case '\b':
      case KEY_BACKSPACE:
        if (chars == 0) break;
        if (index < chars) {
          nameBuffer[chars] = ' ';
          memmove(&nameBuffer[index-1], &nameBuffer[index], (chars-index)*sizeof(char*));
        } else {
          nameBuffer[index-1] = ' ';
        } 

        if (offset > 0) offset--;
        chars--;
        index--;
        wmove(activeWindow,0,0);
        waddnstr(activeWindow, &nameBuffer[offset], (COLS/4)+13);
        if (offset == 0) wmove(activeWindow,y,x-1);
        break;
      case KEY_RIGHT:
        if (index < chars && chars < 100){
          if(x == nameWidth){
            offset++;
          }else{
            index++;
            wmove(name, y, x + 1);
          }
        } 
        break;
      case KEY_LEFT:
        if (index > 0){
          index--;
          wmove(name, y, x - 1);
        } 
        break;
      // case KEY_UP:
      //   if (y == 1 && x < 14) wmove(prompt, y-1, 14); 
      //   else if (y > 0) wmove(prompt, y-1, x);
      //   break;
      // case KEY_DOWN:
      //   if (y == 0 && chars < width - 14) break;
      //   if (chars2pos + width >= chars) wmove(prompt, y+1, chars + 14 - ((y+1)*(width+1)));
      //   else if ( y < (LINES/2)-4) wmove(prompt, y+1, x);
      //   break;
      default:
        if (index < chars) {
          memmove(&nameBuffer[index+1], &nameBuffer[index], (chars-index)*sizeof(char*));
        } 
        if(x == nameWidth - 1) {
          offset++;
        }
        if (chars < 100) {
          nameBuffer[index] = i;
          chars++;
          index++;
          wmove(name,0,0);
          waddnstr(name, &nameBuffer[offset], (COLS/4)+13);
          wmove(name,y,++x);
        }
        break;
    }

#ifdef DEBUG
  wclear(debug);
  box(debug,0,0);
  wmove(debug,1,1);
  wprintw(debug, nameBuffer);
  wmove(debug,2,1);
  wprintw(debug, "offset: %i index: %i chars: %i", offset, index, chars);
  wmove(debug,3,1);
  wprintw(debug, "x: %i, y: %i", x, y);
  wmove(debug,4,1);
  wprintw(debug, "width: %i nameWidth: %i",width, nameWidth);
  wrefresh(debug);
#endif

  }

  curs_set(0);
  wrefresh(prompt);
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

void selectTicket(int key) {
  if (tickets[menuSelection] == NULL) return;

  Ticket *i;

  switch(key) {
    case KEY_DOWN:
      i = tickets[menuSelection];
      if (ticketSelection->next == NULL) return;
      while(i->id != ticketSelection->id) i=i->next;

      if (i->next->pos >= LINES || i->next->pos == 3) {
        scrollPosition[menuSelection]++;
        wclear(menus[menuSelection]);
        drawMenu(menus[menuSelection], title[menuSelection]);
        drawList(menuSelection);
      } 

      dimTicket(ticketSelection);
      ticketSelection = i->next;
      illuminateTicket(ticketSelection);
      break;
    case KEY_UP:
      i = tickets[menuSelection];
      if (i->id == ticketSelection->id) break;

      while(i->next->id != ticketSelection->id && i->next != NULL) i=i->next;
      if (i->pos == -1 ) {
        scrollPosition[menuSelection]--;
        wclear(menus[menuSelection]);
        drawMenu(menus[menuSelection], title[menuSelection]);
        drawList(menuSelection);
      } 

      dimTicket(ticketSelection);
      ticketSelection = i;
      illuminateTicket(ticketSelection);
      break;
    case KEY_RIGHT:
      if (menuSelection < 3) {
        i = tickets[++menuSelection];
        dimTicket(ticketSelection); 
        while(i->pos < ticketSelection->pos && i->next != NULL) i = i->next;
        ticketSelection = i;
        illuminateTicket(ticketSelection);
      }
      break;
    case KEY_LEFT:
      if (menuSelection > 0) {
        i = tickets[--menuSelection];
        dimTicket(ticketSelection); 
        int top = ticketSelection->pos - ticketSelection->size;
        while(i->pos-i->size < top && i->next != NULL) i = i->next;
        ticketSelection = i;
        illuminateTicket(ticketSelection);
      }
      break;
    default:
      break;
  }
}

void selectMenu(int key) {
  switch(key) {
    case KEY_RIGHT:
      dimMenu(menuSelection);
      if(menuSelection < 3) menuSelection++; 
      illuminateMenu(menuSelection);
      break;
    case KEY_LEFT:
      dimMenu(menuSelection);
      if(menuSelection > 0) menuSelection--;
      illuminateMenu(menuSelection);
      break;
    default:
      break;
  }
}

WINDOW *newMenu(int x){
  return newwin(LINES,WWIDTH,0,x);
}

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
