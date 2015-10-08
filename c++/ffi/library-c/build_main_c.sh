#!/bin/sh

gcc -c main.c -I.
gcc -o a.out main.o -L. -lnewmath
