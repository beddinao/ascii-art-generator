#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Usage ./convert.sh [path to png file]"
	exit 1
fi

if [ -f $1 ];
then
	./compile
	./a.out $1
	rm a.out
else
	echo "file" $1 "does not exist"
fi
