package main

import (
	"fmt"
	"os"
	"strconv"
)

func main() {
	args := os.Args
	if len(args) < 2 {
		fmt.Printf("Usage of %s: <number>\n", args[0])
		return
	}

	num, error := strconv.Atoi(args[1])
	if error != nil {
		panic(error)
	}
	fmt.Println(num)
}
