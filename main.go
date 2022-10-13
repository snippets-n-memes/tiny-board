package main

// #cgo CFLAGS: -g -Wall 
// #cgo LDFLAGS: -lncurses
// #include <stdlib.h>
// #include "main.h"
import "C"

func main() {
	C.run()
}