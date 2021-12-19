#!/bin/bash

cantidad_de_threads=1
FORMAT="threads_lectura,thread_maximo,tiempo,output"
directory="data/CargaDeArchivos"

sin_concurrencia=0
con_concurrencia=1

cd ..
make clean
make
rm -rf temp.txt out.txt

# Vamos a ejecutar CargarArchivos con muchos archivos

mkdir -p output/experimento2
mkdir -p output/experimento2/lectura_con_concurrencia/
mkdir -p output/experimento2/lectura_sin_concurrencia/


echo $FORMAT > output/experimento2/lectura_sin_salida-threads-lectura.csv

declare -a archivos
for file in data/carga_de_archivos/*
do 
	archivos+=($file)
	archivos+=" "
	./build/ContarPalabras $cantidad_de_threads $cantidad_de_threads $con_concurrencia ${archivos[@]} &> out.txt
    DATA=$(<out.txt)
    echo $DATA &>> temp.txt
	echo "$cantidad_de_threads threads cargando archivos"
	maximo=$(awk '{print $2"="$3}' temp.txt)
	awk -v threads_lectura=$cantidad_de_threads -v threads_maximo=$cantidad_de_threads -v salida=$maximo '{print threads_lectura","threads_maximo","$1","salida}' temp.txt &>> output/experimento2/lectura_con_concurrencia/salida-threads-lectura.csv 
	((cantidad_de_threads=cantidad_de_threads+1))
    #incrementamos la cantidad de threads para cargar los archivos
	rm temp.txt out.txt
done

echo $FORMAT > output/experimento2/lectura_con_concurrencia/salida-threads-lectura.csv

declare -a archivos
for file in data/carga_de_archivos/*
do 
	archivos+=($file)
	archivos+=" "
	./build/ContarPalabras 1 1 0 ${archivos[@]} &> out.txt
    DATA=$(<out.txt)
    echo $DATA &>> temp.txt
	echo "un thread cargando $cantidad_de_threads archivos"
	maximo=$(awk '{print $2"="$3}' temp.txt)
	awk -v threads_lectura=$cantidad_de_threads -v threads_maximo=$cantidad_de_threads -v salida=$maximo '{print threads_lectura","threads_maximo","$1","salida}' temp.txt &>> output/experimento2/lectura_con_concurrencia/salida-threads-lectura.csv 
	((cantidad_de_threads=cantidad_de_threads+1))
    #incrementamos la cantidad de threads para cargar los archivos
	rm temp.txt out.txt
done
