package main

// #cgo CFLAGS: -g -Wall
// #include "structs.h"
import "C"
import "fmt"
import "unsafe"
import "encoding/json"

type test struct {
	Id int
	Name string
}

func main() {
	// initialize a struct in C, pass to Go
	f := C.getStruct();
	fmt.Println(C.GoString((*C.struct_Test)(unsafe.Pointer(f)).Name));
	fmt.Println((*C.struct_Test)(unsafe.Pointer(f)).Id);

	// initialize a struct (defined in c) in Go
	g := C.struct_Test{
		Id: 50, 
		Name: C.CString("Different text"),
	};

	fmt.Println(C.GoString(g.Name))
	fmt.Println(g.Id)

	// print the structs to json
	jsonOutput1, _ := json.Marshal(&f)
	fmt.Println(string(jsonOutput1))
	jsonOutput2, _ := json.Marshal(&g)
	fmt.Println(string(jsonOutput2))
}

func convert(_Ctype_Test in) test* {
	return &test{
		in.Id,
		C.GoString(in.Name),
	}
}

/*
https://go.dev/ref/spec#Exported_identifiers

Exported identifiers
An identifier may be exported to permit access to it from another package. An identifier is exported if both:

the first character of the identifier's name is a Unicode uppercase letter (Unicode character category Lu); and
the identifier is declared in the package block or it is a field name or method name.
All other identifiers are not exported.

https://go.dev/ref/spec#Conversions
use a conversion to make structs with c char* types to structs with go string types
*/