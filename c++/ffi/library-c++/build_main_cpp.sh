#!/bin/sh

g++ -c -I. main.cpp
g++ -o a.out -L. -lcstack main.o
