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
)

func main() {
	C.initializeBoard();
	var tickets **C.Ticket;
	for i := 0; i<10; i++ {
		tickets = C.run()
	}

	clear := exec.Command("clear")
	clear.Stdout = os.Stdout
	clear.Run();
	p := (*[]C.Ticket)tickets
	fmt.Print((*p)[0])
	fmt.Print("done.\n")
}