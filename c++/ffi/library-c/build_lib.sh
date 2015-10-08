#!/bin/sh

case "`uname`" in
    CYGWIN*)
        gcc -shared -std=c99 -o newmath.dll newmath.c
        echo 'create newmath.dll'
        ;;
    Darwin*)
        gcc -shared -o libnewmath.dylib newmath.c
        echo 'create libnewmath.dylib'
        ;;
    *)
        echo 'failed to create a dynamic library'
        ;;
esac
