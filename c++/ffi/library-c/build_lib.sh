#!/bin/sh

case "`uname`" in
    CYGWIN*)
        echo 'Create newmath.dll'
        gcc -shared -std=c99 -o newmath.dll newmath.c
        ;;
    Darwin*)
        echo 'Create libnewmath.dylib'
        gcc -shared -std=c99 -o libnewmath.dylib newmath.c
        ;;
    Linux*)
        echo 'Create libnewmath.so'
        gcc -shared -std=c99 -o libnewmath.so newmath.c
        ;;
    *)
        echo 'Failed to create a dynamic library'
        ;;
esac
