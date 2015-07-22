#!/bin/sh

case "`uname`" in
    CYGWIN*)
        g++ -shared -o cstack.dll cstack.cpp
        echo 'create cstack.dll'
        ;;
    Darwin*)
        g++ -shared -o libcstack.dylib cstack.cpp
        echo 'create libcstack.dylib'
        ;;
    *)
        echo 'failed to create a dynamic library'
        ;;
esac
