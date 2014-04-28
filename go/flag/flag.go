package main

import (
	"flag"
	"fmt"
)

func main() {
	var boolFlag bool
	var stringFlag string
	flag.BoolVar(&boolFlag, "b", false, "bool flag")
	flag.BoolVar(&boolFlag, "bool", false, "bool flag")
	flag.StringVar(&stringFlag, "s", "", "string flag")
	flag.StringVar(&stringFlag, "string", "", "string flag")
	flag.Parse()

	fmt.Println("bool flag =", boolFlag)
	fmt.Println("string flag =", stringFlag)
}
