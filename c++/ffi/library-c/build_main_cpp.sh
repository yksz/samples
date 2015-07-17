#!/bin/sh

g++ -c -I. main.cpp
g++ -o a.out -L. -lnewmath main.o
