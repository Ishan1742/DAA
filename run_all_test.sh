#!/bin/bash

echo -e "Creating test cases...\n"
echo -e "Creating tests for increasing text length...\n"
cd ./tests/text-length
python3 test_creator.py
echo -e "Creating tests for increasing pattern length...\n"
cd ../pattern-length
python3 test_creator.py 
echo -e "Creating tests for Increasing pattern count...\n"
cd ../pattern-count 
python3 test_creator.py
echo -e "Done...\n\n"

echo -e "--*** Aho Chorasick Benchmark***---\n"

echo -e "Running benchmarks... \n"
cd ../../aho-corasick/
g++ -std=c++11 benchmark-text-length.cpp aho_corasick.hpp -o text-length.o
g++ -std=c++11 benchmark-pattern-length.cpp aho_corasick.hpp -o pattern-length.o
g++ -std=c++11 benchmark-pattern-count.cpp aho_corasick.hpp -o pattern-count.o

echo -e "Increasing Text Length... \n"
./text-length.o
echo -e "Increasing Pattern Length... \n"
./pattern-length.o
echo -e "Increasing Pattern Count... \n"
./pattern-count.o
echo -e "Done... \n"

echo -e "--*** Rabin Karp Benchmark***---\n"

echo -e "Running benchmarks... \n"
cd ../karp-rabin
g++ -std=c++11 benchmark-text-length.cpp -o text-length.o
g++ -std=c++11 benchmark-pattern-length.cpp -o pattern-length.o
g++ -std=c++11 benchmark-pattern-count.cpp -o pattern-count.o

echo -e "Increasing Text Length... \n"
./text-length.o
echo -e "Increasing Pattern Length... \n"
./pattern-length.o
echo -e "Increasing Pattern Count... \n"
./pattern-count.o
echo -e "Done... \n"

echo -e "Plotting Results... \n"
cd ..
python3 graph_generator.py
echo -e "Done... \n"

cd ./karp-rabin
rm *.txt
rm *.o

cd ../aho-corasick
rm *.txt
rm *.o

cd ../tests/pattern-count 
rm *.txt
cd ../pattern-length
rm *.txt
cd ../text-length
rm *.txt