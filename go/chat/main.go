package main

import (
	"./chat"
	"flag"
)

var port int

func init() {
	flag.IntVar(&port, "port", 8080, "port number")
	flag.Parse()
}

func main() {
	server := chat.NewServer(port)
	server.Start()
}
