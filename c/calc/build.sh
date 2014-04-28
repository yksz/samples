#!/bin/sh

if [ -n "$cygwin" ]; then
    byacc -dv calc.y
    flex calc.l
else
    yacc -dv calc.y
    lex calc.l
fi
gcc -o calc y.tab.c lex.yy.c
