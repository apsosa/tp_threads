#!/bin/bash

file1='data/corpus'
#cat $file1 funciona!

cd ..
make clean
make
rm -rf output
mkdir output

echo "iteracion,threads,tiempo,output" > output/corpus.csv

for i in {1..26}
do  
    ./build/ContarPalabras $i $i $file1  &>> output/salida.csv
done
