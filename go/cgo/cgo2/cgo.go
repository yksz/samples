package main

// #cgo CFLAGS: -I.
// #cgo LDFLAGS: ./libhello.a
// #include "hello.h"
import "C"

func main() {
	C.hello()
}
