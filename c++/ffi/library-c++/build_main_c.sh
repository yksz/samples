#!/bin/sh

gcc -c -I. main.c
gcc -o a.out -L. -lcstack main.o
