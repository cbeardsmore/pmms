#! /bin/bash

# COMPILE PROGRAM
make multiThread

# RUN PROGRAM FOR COMBINATION OF M N K VALUES
# FROM 1 TO 100
for i in {96..1};
do
	for j in {74..1};
	do
		for k in {64..1};
		do
			echo $i $j $k
			./multiThread ma2.txt ma2.txt $i $j $k
		done
	done
done