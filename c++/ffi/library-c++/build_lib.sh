#!/bin/sh

case "`uname`" in
    CYGWIN*)
        g++ -shared -o cstack.dll cstack.cpp
        echo 'create cstack.dll'
        ;;
    *)
        echo 'failed to create a dynamic library'
        ;;
esac
