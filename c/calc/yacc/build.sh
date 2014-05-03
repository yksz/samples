#!/bin/sh

if [ -n "$cygwin" ]; then
    byacc -dv calc.y
else
    yacc -dv calc.y
fi
gcc -o calc y.tab.c
