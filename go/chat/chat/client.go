package chat

import (
	"bufio"
	"net"
	"strconv"
)

var id int

type client struct {
	id     int
	conn   net.Conn
	reader *bufio.Reader
	writer *bufio.Writer
}

func newClient(conn net.Conn) *client {
	id++
	return &client{
		id,
		conn,
		bufio.NewReader(conn),
		bufio.NewWriter(conn)}
}

func (c *client) String() string {
	return "client [id=" + strconv.Itoa(c.id) + "]"
}
