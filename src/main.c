#include "main.h"

WINDOW *menus[4];
Ticket *tickets[4];
Ticket *ticketSelection;
Selecting level = ticket;

int key = 0;
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

  textField *ticketName = newTextField(1, (COLS/2)-17, (LINES/4)+2,(COLS/4)+14);
  initializeBuffer(ticketName, 100);

  textField *activeField = ticketName;
  WINDOW *activeWindow = ticketName->win;
  char *activeBuffer = ticketName->buffer;

  wrefresh(activeWindow);
  curs_set(1);
  keypad(activeWindow, TRUE);
  int i = 0, x = 0, y = 0, 
      chars = 0, index = 0, offset = 0, fieldWidth;

  while(i != 10){
    getyx(activeWindow, y, x);
    wrefresh(activeWindow);
    i = wgetch(activeWindow);
    fieldWidth = activeField->width;

    switch (i){
      case 127:
      case '\b':
      case KEY_BACKSPACE:
        if (chars == 0 || index == 0) break;
        if (index < chars) {
          activeBuffer[chars] = ' ';
          memmove(&activeBuffer[index-1], &activeBuffer[index], (chars-index)*sizeof(char*));
        } else {
          activeBuffer[index-1] = ' ';
        } 

        if (offset > 0 && x == 0) offset--;

        chars--;
        index--;
        wmove(activeWindow,0,0);
        waddnstr(activeWindow, &activeBuffer[offset], fieldWidth);
        if (x > 0) wmove(activeWindow,y,x-1);
        else wmove(activeWindow,y,x);
        break;
      case KEY_RIGHT:
        if (index < chars && chars < 100){
          if(x == fieldWidth-1){
            index++;
            offset++;
            wmove(activeWindow,0,0);
            waddnstr(activeWindow, &activeBuffer[offset], fieldWidth);
            wmove(activeWindow,0,fieldWidth-1);
          }else{
            index++;
            wmove(activeWindow, y, x + 1);
          }
        } 
        break;
      case KEY_LEFT:
        if (offset > 0 && x == 0){
          index--;
          offset--;
          waddnstr(activeWindow, &activeBuffer[offset], fieldWidth);
          wmove(activeWindow,0,0);
        } else if (index > 0){
          index--;
          wmove(activeWindow, y, x - 1);
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
          memmove(&activeBuffer[index+1], &activeBuffer[index], (chars-index)*sizeof(char*));
        } 
        if(x == fieldWidth - 1) {
          offset++;
        }
        if (chars < 100) {
          activeBuffer[index] = i;
          chars++;
          index++;
          wmove(activeWindow,0,0);
          waddnstr(activeWindow, &activeBuffer[offset], fieldWidth);
          wmove(activeWindow,y,++x);
        }
        break;
    }

#ifdef DEBUG
  getyx(activeWindow, y, x);
  wclear(debug);
  box(debug,0,0);
  wmove(debug,1,1);
  wprintw(debug, activeBuffer);
  wmove(debug,2,1);
  wprintw(debug, "offset: %i index: %i chars: %i", offset, index, chars);
  wmove(debug,3,1);
  wprintw(debug, "x: %i, y: %i", x, y);
  wmove(debug,4,1);
  wprintw(debug, "width: %i fieldWidth: %i",width, fieldWidth);
  wrefresh(debug);
#endif

  }

  curs_set(0);
  wrefresh(prompt);
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
