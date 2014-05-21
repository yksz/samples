package main

import (
	"flag"
	"io"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"strings"
)

const maxMemory = 10000000 // 10MB

var port string

func init() {
	flag.StringVar(&port, "port", "8080", "port number")
	flag.Parse()
}

func uploadHandler(w http.ResponseWriter, req *http.Request) {
	err := req.ParseMultipartForm(maxMemory)
	if err != nil {
		log.Print(err)
		return
	}
	for key, _ := range req.MultipartForm.File {
		file, fileHeader, err := req.FormFile(key)
		if err != nil {
			log.Print(err)
			return
		}
		defer file.Close()
		saveFile(file, fileHeader.Filename)
	}
}

func saveFile(r io.Reader, path string) {
	if path == "" {
		return
	}
	if strings.HasPrefix(path, "/") {
		path = path[1:]
	}
	index := strings.LastIndex(path, "/")
	if index != -1 {
		dir := path[:index]
		os.MkdirAll(dir, os.ModeDir)
	}
	bytes, _ := ioutil.ReadAll(r)
	ioutil.WriteFile(path, bytes, 0644)
	log.Printf("save a file: %s", path)
}

func main() {
	log.Print("the upload server started: port=" + port)
	http.HandleFunc("/", uploadHandler)
	http.ListenAndServe(":"+port, nil)
}
