#!/bin/sh

if [ $# -lt 1 ] ; then
    echo "usage: $0 <sql file>"
    exit 1
fi

DB_NAME='test.db'
sql_file=$1
sqlite3 $DB_NAME < $sql_file
rm $DB_NAME
