#!/bin/bash

if [ $# -lt 2 ]; then
	echo "usage: bash map_gen.sh [size] [range]"
	exit 1
fi

unset var
for i in $( seq 1 $1 )
do
	var+="\n$(( RANDOM % $2 + 1))"
done
var="${var}\n";
echo -e $var | tail -n +2

