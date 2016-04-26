#! /bin/bash

# COMPILE PROGRAM
make pmms

# RUN PROGRAM FOR COMBINATION OF M N K VALUES
# FROM 1 TO 100
for i in {100..1};
do
	for j in {100..1};
	do
		for k in {100..1};
		do
			echo $i $j $k
			./pmms ma2.txt ma2.txt $i $j $k
		done
	done
done