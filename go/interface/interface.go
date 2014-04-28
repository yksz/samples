package main

import (
	"fmt"
)

type Animal interface {
	talk() string
}

type Cat struct {
	name string
}

func (c *Cat) talk() string {
	return c.name + ": Meow!"
}

type Dog struct {
	name string
}

func (d *Dog) talk() string {
	return d.name + ": Woof!"
}

func main() {
	cat := new(Cat)
	cat.name = "cat"
	dog := &Dog{"dog"}
	fmt.Println(cat.talk())
	fmt.Println(dog.talk())
}
