#!/bin/sh

export GRADLE_OPTS="-Xdebug -Xrunjdwp:transport=dt_socket,address=9999,server=y,suspend=n"
gradle jettyRun
