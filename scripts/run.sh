#!/bin/bash

FORMAT="iteracion,threads,tiempo,output"
file1='data/corpus'
#cat $file1 funciona!

cd ..
make clean
make
rm -rf output
mkdir output

echo $FORMAT > output/salida.csv

for i in {1..26}
do  
    ./build/ContarPalabras $i $i $file1 &> temp.txt
    DATA=$(<temp.txt)
    echo $DATA &> temp.txt
    awk -v iteracion=$i -v threads=$i '{print iteracion","threads","$1","$2 $3}' temp.txt &>> output/salida.csv
done

rm -rf temp.txt
