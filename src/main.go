package main

// #cgo CFLAGS: -g -Wall
// #cgo LDFLAGS: -lncurses
// #include <stdlib.h>
// #include "main.h"
import "C"
import (
	"fmt"
)

func main() {
	C.initializeBoard();
	for C.run() == 1 {
		C.getTickets();
	}
}