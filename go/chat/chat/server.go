package chat

import (
	"io"
	"log"
	"net"
	"strconv"
)

type Server struct {
	port    int
	clients map[int]*client
	message chan string
}

func NewServer(port int) *Server {
	return &Server{port, make(map[int]*client), make(chan string, 1)}
}

func (s *Server) Start() {
	log.Print("the chat server is listening on port " + strconv.Itoa(s.port))
	ln, err := net.Listen("tcp", ":"+strconv.Itoa(s.port))
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
		c := newClient(conn)
		s.clients[c.id] = c
		go s.receive(c)
	}
}

func (s *Server) receive(c *client) {
	log.Printf("connect: %v", c)
	for {
		line, err := c.reader.ReadString('\n')
		if err == io.EOF {
			log.Printf("disconnect: %v", c)
			delete(s.clients, c.id)
			c.conn.Close()
			return
		}
		if err != nil {
			log.Print(err)
			continue
		}
		s.message <- line
	}
}

func (s *Server) broadcast() {
	for {
		msg := <-s.message
		log.Print("message=" + msg)
		for _, c := range s.clients {
			c.writer.WriteString(msg)
			c.writer.Flush()
		}
	}
}
