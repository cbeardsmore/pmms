#! /bin/bash

# AUTHOR: Connor Beardsmore
# DATE: 07/04/16

# COMPILE PROGRAM
make pmms

# RUN PMMS PROGRAM FOR COMBINATION OF M N K VALUES
# FROM 1 TO 100

for i in {1..100};
do
    for j in {1..100};
    do
        for k in {1..100};
        do
            echo $i $j $k
            ./pmms allOnes.txt allOnes.txt $i $j $k
        done
    done
done
