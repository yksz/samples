#!/bin/sh

if [ $# -lt 1 ]; then
    echo 'usage: ./sql.sh <sql file>'
    exit 1
fi

db='test.db'
sql=$1
sqlite3 $db < $sql
rm $db
