package main

import (
	"flag"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"strings"
	"time"
)

const maxMemory = 10000000 // 10MB

var port string

func init() {
	flag.StringVar(&port, "port", "8080", "port number")
	flag.Parse()
}

func uploadHandler(w http.ResponseWriter, req *http.Request) {
	defer func() {
		if r := recover(); r != nil {
			msg := fmt.Sprintf("%v", r)
			log.Print(msg)
			http.Error(w, msg, http.StatusInternalServerError)
		}
	}()
	err := req.ParseMultipartForm(maxMemory)
	check(err)
	for key, _ := range req.MultipartForm.File {
		file, fileHeader, err := req.FormFile(key)
		check(err)
		defer file.Close()
		checkFilename(fileHeader.Filename)
		year, month, day := time.Now().Date()
		dir := fmt.Sprintf("%d-%d-%d", year, int(month), day)
		err = saveFile(file, dir+"/"+fileHeader.Filename)
		check(err)
	}
}

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func checkFilename(filename string) {
	if filename == "" {
		panic(fmt.Sprintf("filename not found: %s", filename))
	}
	if strings.Index(filename, "..") != -1 { // security
		panic(fmt.Sprintf("filename is invalid: %s", filename))
	}
}

func saveFile(r io.Reader, path string) error {
	index := strings.LastIndex(path, "/")
	if index != -1 {
		dir := path[:index]
		err := os.MkdirAll(dir, 0755)
		if err != nil {
			return err
		}
	}
	bytes, err := ioutil.ReadAll(r)
	if err != nil {
		return err
	}
	err = ioutil.WriteFile(path, bytes, 0644)
	if err != nil {
		return err
	}
	log.Printf("save a file: %s", path)
	return nil
}

func main() {
	log.Print("the upload server is listening on port " + port)
	http.HandleFunc("/", uploadHandler)
	http.ListenAndServe(":"+port, nil)
}
