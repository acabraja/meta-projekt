#!/bin/bash

clear

echo "Ovo je skripra koja kompajlira datoteke za 3sat."
echo  "Trenutno nije u funkciji pa je kompajliranje obicno."
echo  "Pricekajte trenutak i pratite upute "
g++ main.cpp 3sat.cpp mtrand/mtrand.cpp -pthread -o main

#echo "kompajliram 3sat.cpp"
#g++ -c 3sat.cpp -o 3sat

#echo "kompajliram main.cpp i linkam"

#g++ -c main.cpp 3sat -pthread -o main


echo " pokreni ./main"
