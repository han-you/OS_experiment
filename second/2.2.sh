#!/bin/bash
for var in `seq 1 9`
do
	for var2 in `seq 1 $var`
	do
		let tmp=$var\*$var2
		echo -n "$var * $var2=$tmp "
	done
echo""
done
