#!bin/bash
file1="main.c"
file2="func.c"
file3="func.h"
total=0
lines=$(find $file1 -name "$file1" | xargs cat | wc -l)
let total=total+lines
echo "$file1:$lines"
lines=$(find $file2 -name "$file2" | xargs cat | wc -l)
let total=total+lines
echo "$file2:$lines"
lines=$(find $file3 -name "$file3" | xargs cat | wc -l)
let total=total+lines
echo "$file3:$lines"
echo "total:$total"
