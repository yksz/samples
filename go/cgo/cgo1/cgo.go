package main

// #include <stdlib.h>
import "C"
import "fmt"

func main() {
	x := C.abs(-100)
	fmt.Println(x)
}
