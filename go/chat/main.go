package main

import (
	"./chat"
	"flag"
)

var port string

func init() {
	flag.StringVar(&port, "port", "8080", "port number")
	flag.Parse()
}

func main() {
	server := chat.NewServer(port)
	server.Start()
}
