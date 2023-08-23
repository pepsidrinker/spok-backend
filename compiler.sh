#!/bin/bash

echo "Compiling main.cpp ..."

rm *.o
rm *.gch
rm Includes/*.o
rm Includes/*.gch
rm Include/Learners/Movement/*.o
rm Include/Learners/Movement/*.gch

rm a.out

g++ --std=c++17 -Wall -g -c -fPIC Include/Learners/Movement/*.cpp -lpthread
g++ --std=c++17 -Wall -g -c -fPIC Include/*.cpp -lpthread
g++ --std=c++17 -Wall -g -c main.cpp -lpthread
g++ --std=c++17 -Wall -g *.o -o a.out -lpthread

echo "Cleaning ..."
rm *.o
rm *.gch
rm Includes/*.o
rm Includes/*.gch
rm Include/Learners/Movement/*.o
rm Include/Learners/Movement/*.gch

exit 0