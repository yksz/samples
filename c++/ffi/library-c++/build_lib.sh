#!/bin/sh

case "`uname`" in
    CYGWIN*)
        echo 'Create cstack.dll'
        g++ -shared -o cstack.dll cstack.cpp
        ;;
    Darwin*)
        echo 'Create libcstack.dylib'
        g++ -shared -o libcstack.dylib cstack.cpp
        ;;
    Linux*)
        echo 'Create libcstack.so'
        g++ -shared -fPIC -o libcstack.so cstack.cpp
        ;;
    *)
        echo 'Failed to create a dynamic library'
        ;;
esac
