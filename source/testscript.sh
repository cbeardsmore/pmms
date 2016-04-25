#! /bin/bash

for ( i=1; i<=100; i++ );
do
	for ( j=1; j<=100; j++ );
	do
		for ( k=1; k<=100; k++ );
		do
			./multiProcess ma2.txt ma2.txt $i $j $k
		done
	done
done