package main

// #cgo CFLAGS: -g -Wall
// #include "structs.h"
import "C"
import "fmt"

type Test struct{
	id, name
}

func main() {
	f := C.getStruct();
	fmt.Println(f.name);
}