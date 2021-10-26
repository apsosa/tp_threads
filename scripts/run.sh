#!/bin/bash

cantidad_de_letras=26
FORMAT="threads_lectura,thread_maximo,tiempo_mediana,output"
file1='data/corpus'
#cat $file1 funciona!

cd ..
make clean
make
rm -rf output temp.txt out.txt
mkdir output

echo $FORMAT > output/salida.csv

for i in {1..26}
do  
    for j in {1..5} 
    do        
        ./build/ContarPalabras 1 $i $file1 &> out.txt
        DATA=$(<out.txt)
        echo $DATA &>> temp.txt
    done 
    
    maximo=$(sed -n 1p temp.txt | awk '{print $2"="$3}')
    awk '{print $1}' temp.txt | sort &> sorted.txt
    sed -n 3p sorted.txt > median.txt
    awk -v threads_lectura=1 -v threads_maximo=$i -v salida=$maximo '{print threads_lectura","threads_maximo","$1","salida}' median.txt &>> output/salida.csv
    rm temp.txt out.txt sorted.txt median.txt
done

