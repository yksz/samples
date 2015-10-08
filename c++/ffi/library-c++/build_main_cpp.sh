#!/bin/sh

g++ -c main.cpp -I.
g++ -o a.out main.o -L. -lcstack
