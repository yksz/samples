package main

import (
	"./newmath"
	"fmt"
)

func main() {
	slice := []int{1, 2, 3}
	sum := newmath.Sum(slice)
	fmt.Println(sum)
}
