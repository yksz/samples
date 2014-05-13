package main

import (
	"bytes"
	"flag"
	"io"
	"io/ioutil"
	"log"
	"net/http"
	"strconv"
	"strings"
)

var port string

func init() {
	flag.StringVar(&port, "port", "8080", "port number")
	flag.Parse()
}

func echoHandler(w http.ResponseWriter, req *http.Request) {
	header := toString(req.Header)
	io.WriteString(w, header)
	body, err := ioutil.ReadAll(req.Body)
	if err != nil {
		log.Print(err)
		return
	}
	w.Write(body)
	w.Header().Add("Content-Length", strconv.Itoa(len(header)+len(body)))
}

func toString(header http.Header) string {
	var buf bytes.Buffer
	for k, v := range header {
		buf.WriteString(k)
		buf.WriteString(": ")
		buf.WriteString(strings.Join(v, "; "))
		buf.WriteString("\n")
	}
	buf.WriteString("\n")
	return buf.String()
}

func main() {
	log.Print("the echo server started: port=" + port)
	http.HandleFunc("/", echoHandler)
	http.ListenAndServe(":"+port, nil)
}
