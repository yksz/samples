#!/bin/sh

if [ $# -lt 1 ] ; then
    echo "usage: $0 <sql file>"
    exit 1
fi

db='test.db'
sql=$1
sqlite3 $db < $sql
rm $db
