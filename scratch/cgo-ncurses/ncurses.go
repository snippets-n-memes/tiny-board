package main

// #cgo CFLAGS: -g -Wall
// #cgo LDFLAGS: -lncurses
// #include <ncurses.h>
// #include <main.h>
import "C"
// import "fmt"
// import "unsafe"
// import "encoding/json"

func main() {
  C.initializeBoard();
}