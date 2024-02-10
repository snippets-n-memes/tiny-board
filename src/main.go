package main

// #cgo CFLAGS: -g -Wall
// #cgo LDFLAGS: -lncurses
// #include <stdlib.h>
// #include "main.h"
import "C"
import (
	"fmt"
	"os"
	"os/exec"
	"unsafe"
	"strings"
)

type Ticket C.Ticket

func main() {
	C.initializeBoard();
	var tickets **C.Ticket;

	for C.run() == 1 {
		tickets = C.getMenuLists();
	}
	
	C.deleteMenus();
	C.endwin();
	C.curs_set(1)
	C.refresh();

	clear := exec.Command("reset")
	clear.Stdout = os.Stdout
	clear.Run();

	ticketSlice := (*[1 << 30]*C.Ticket)(unsafe.Pointer(tickets))[:4:4]

	fmt.Println("unnassinged:")
	ticket := ticketSlice[0];
	for ticket != nil {
		fmt.Print("   "+strings.TrimSpace(C.GoString(ticket.name)))
		fmt.Print("- "+strings.TrimSpace(C.GoString(ticket.description)))
		ticket = ticket.next
	}
}