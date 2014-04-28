package chat

import (
	"io"
	"log"
	"net"
)

type Server struct {
	port    string
	clients map[int]*client
	message chan string
}

func NewServer(port string) *Server {
	return &Server{port, make(map[int]*client), make(chan string, 1)}
}

func (s *Server) Start() {
	log.Print("the chat server started: port=" + s.port)
	ln, err := net.Listen("tcp", ":"+s.port)
	if err != nil {
		log.Fatal(err)
	}
	s.accept(ln)
}

func (s *Server) accept(listener net.Listener) {
	defer listener.Close()
	go s.broadcast()
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		client := newClient(conn)
		s.clients[client.id] = client
		go s.receive(client)
	}
}

func (s *Server) receive(client *client) {
	log.Printf("connect: %v", client)
	for {
		line, err := client.reader.ReadBytes('\n')
		if err != nil {
			if err == io.EOF {
				log.Printf("disconnect: %v", client)
				delete(s.clients, client.id)
				return
			}
			log.Print(err)
		} else {
			s.message <- string(line)
		}
	}
}

func (s *Server) broadcast() {
	for {
		msg := <-s.message
		log.Print("message=" + msg)
		for _, client := range s.clients {
			client.writer.WriteString(msg)
			client.writer.Flush()
		}
	}
}
