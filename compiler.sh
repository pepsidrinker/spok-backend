#!/bin/bash

echo "Compiling main.cpp ..."

rm *.o
rm *.gch
rm Includes/*.o
rm Includes/*.gch
rm a.out

g++ --std=c++17 -Wall -g -c -fPIC Include/*.cpp -lpthread
g++ --std=c++17 -Wall -g -c main.cpp -lpthread
g++ --std=c++17 -Wall -g *.o -o a.out -lpthread

echo "Cleaning ..."
rm *.o
rm *.gch
rm Includes/*.o
rm Includes/*.gch

exit 0