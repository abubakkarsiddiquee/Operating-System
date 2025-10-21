#!/bin/bash
read -p "> Enter a directory to scan for shell scripts: " directory

if [ ! -d "$directory" ]; then
echo "Dir does not exist"
exit 1

fi

files=($(find "$directory" -type f -name "*.sh"))

read -p "> Enter a keyword to count in the found scripts: " keyword

for file in "${files[@]}"; do
count=$(grep -i -c "$keyword" "$file")
echo "$file : $count occurrences"
done
