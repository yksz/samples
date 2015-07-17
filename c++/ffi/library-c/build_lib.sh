#!/bin/sh

case "`uname`" in
    CYGWIN*)
        g++ -shared -o newmath.dll newmath.c
        echo 'create newmath.dll'
        ;;
    *)
        echo 'failed to create a dynamic library'
        ;;
esac
