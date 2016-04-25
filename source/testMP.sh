#! /bin/bash

# COMPILE PROGRAM
make multiProcess

# RUN PROGRAM FOR COMBINATION OF M N K VALUES
# FROM 1 TO 100
for i in {1..100};
do
	for j in {12..100};
	do
		for k in {86..100};
		do
			echo $i $j $k
			./multiProcess ma2.txt ma2.txt $i $j $k
		done
	done
done