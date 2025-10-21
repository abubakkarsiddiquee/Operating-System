#!/bin/bash
echo -n "Numbers of query : "
read num_query

for ((i=1; i<=num_query; i++))
do

remaining=$((num_query -i + 1))
echo "Have $remaining query remining"

echo -n "Filename: "
read filename

num_line=$(wc -l < "$filename")

echo "Number of line : $num_line"

if [ "$num_line" -eq 0 ]; then
	 echo "$filename is empty"
elif [ "$num_line" -lt 10 ]; then
	echo "$filename is small"
else
	echo "$filename is large."
fi

done
