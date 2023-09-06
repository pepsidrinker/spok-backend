#!/bin/bash

echo "Compiling main.cpp ..."

rm *.o
rm *.gch
rm Includes/*.o
rm Includes/*.gch

rm Include/Learners/*.o
rm Include/Learners/*.gch
rm Include/Learners/Movement/*.o
rm Include/Learners/Movement/*.gch

rm Include/StateReaders/*.o
rm Include/StateReaders/*.gch
rm Include/StateReaders/Memcache/*.o
rm Include/StateReaders/Memcache/*.gch

rm a.out


g++ --std=c++17 -Wall -g -c -fPIC Include/StateReaders/Memcache/*.cpp -lpthread 
g++ --std=c++17 -Wall -g -c -fPIC Include/StateReaders/*.cpp -lpthread

g++ --std=c++17 -Wall -g -c -fPIC Include/Learners/Movement/*.cpp -lpthread
g++ --std=c++17 -Wall -g -c -fPIC Include/Learners/*.cpp -lpthread

g++ --std=c++17 -Wall -g -c -fPIC Include/*.cpp -lpthread
g++ --std=c++17 -Wall -g -c main.cpp -lpthread  -lmemcached -lxxhash
g++ --std=c++17 -Wall -g *.o -o a.out -lpthread  -lmemcached -lxxhash

echo "Cleaning ..."
rm *.o
rm *.gch

rm Includes/*.o
rm Includes/*.gch

rm Include/Learners/*.o
rm Include/Learners/*.gch

rm Include/Learners/Movement/*.o
rm Include/Learners/Movement/*.gch

exit 0