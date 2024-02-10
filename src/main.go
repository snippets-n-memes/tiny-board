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
	tickets = C.run();
	tickets = C.run();
	
	C.deleteMenus();
	C.endwin();
	C.refresh();

	clear := exec.Command("reset")
	clear.Stdout = os.Stdout
	clear.Run();

	ticketSlice := (*[1 << 30]*C.Ticket)(unsafe.Pointer(tickets))[:4:4]

	fmt.Println(strings.TrimSpace(C.GoString(ticketSlice[0].name)))
	fmt.Println(strings.TrimSpace(C.GoString(ticketSlice[0].next.name)))
	fmt.Println("done.\n")


}