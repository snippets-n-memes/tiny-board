package main

// #cgo CFLAGS: -g -Wall
// #include "structs.h"
import "C"
import "fmt"
import "unsafe"

func main() {
	f := C.getStruct();
	fmt.Println(C.GoString((*C.struct_Test)(unsafe.Pointer(f)).name));
	fmt.Println((*C.struct_Test)(unsafe.Pointer(f)).id);
}