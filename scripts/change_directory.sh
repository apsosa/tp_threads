#!/bin/bash

file1='data/corpus'
#cat $file1 funciona!

cd ..
make clean
make

./build/ContarPalabras 3 3 $file1

