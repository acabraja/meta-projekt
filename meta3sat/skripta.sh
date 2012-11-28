#!/bin/bash

clear

echo "Ovo je skripra koja kompajlira datoteke za 3sat"
echo

echo "kompajliram 3sat.cpp"

g++ -c 3sat.cpp -o 3sat

echo "kompajliram main.cpp i linkam"

g++ -c main.cpp 3sat -o main

echo " pokreni ./main"
