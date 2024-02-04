package main

// #cgo CFLAGS: -g -Wall
// #cgo LDFLAGS: -lncurses
// #include <ncurses.h>
// #include <constants.h>
import "C"
// import "fmt"
// import "unsafe"
// import "encoding/json"

func main() {
	C.initscr();
  C.curs_set(0);
  C.refresh();
	C.addstr("This is the standard screen\n");
	C.move(1,0);
  C.printw("WWIDTH = %d", C.WWIDTH);
  C.move(2,0);
  C.printw("LINES = %d", C.LINES);
  C.refresh();
  C.getch();
}