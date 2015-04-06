#!/bin/sh

if [ -z "$FELIX_HOME" ] ; then
    echo "'FELIX_HOME' is not found"
    exit 1
fi

cd $FELIX_HOME
java -jar bin/felix.jar
