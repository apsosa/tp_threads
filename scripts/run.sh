#!/bin/bash

cantidad_de_letras=26
FORMAT="threads_lectura,thread_maximo,tiempo_mediana,output"
directoryRepetidos="data/random-con-repetidos"
directoryNoRepetidos="data/random-sin-repetidos"

cd ..
make clean
make
rm -rf temp.txt out.txt

echo $FORMAT > output/salida.csv

# Para los sin repetidos

for file in data/random-sin-repetidos/*
do
    files=$(basename "$file")
    echo $files
    for i in {1..26}
    do  
        for j in {1..5} 
        do        
            ./build/ContarPalabras 1 $i $file &> out.txt
            DATA=$(<out.txt)
            echo $DATA &>> temp.txt
        done 
        
        maximo=$(sed -n 1p temp.txt | awk '{print $2"="$3}')
        awk '{print $1}' temp.txt | sort &> sorted.txt
        sed -n 3p sorted.txt > median.txt
        awk -v threads_lectura=1 -v threads_maximo=$i -v salida=$maximo '{print threads_lectura","threads_maximo","$1","salida}' median.txt &>> output/salida-$files.csv
        rm temp.txt out.txt sorted.txt median.txt
    done
done

# Para los repetidos

for file in data/random-con-repetidos/*
do
    files=$(basename "$file")
    echo $files
    for i in {1..26}
    do  
        for j in {1..5} 
        do        
            ./build/ContarPalabras 1 $i $file &> out.txt
            DATA=$(<out.txt)
            echo $DATA &>> temp.txt
        done 
        
        maximo=$(sed -n 1p temp.txt | awk '{print $2"="$3}')
        awk '{print $1}' temp.txt | sort &> sorted.txt
        sed -n 3p sorted.txt > median.txt
        awk -v threads_lectura=1 -v threads_maximo=$i -v salida=$maximo '{print threads_lectura","threads_maximo","$1","salida}' median.txt &>> output/salida-$files.csv
        rm temp.txt out.txt sorted.txt median.txt
    done
done
