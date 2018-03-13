
#Makefile

MainClass = nmiMeasure

nmiMeasure : main.o nmiMeasure.o 
	g++ --std=c++11  main.o nmiMeasure.o  -lm -o nmiMeasure

main.o: nmiMeasure.hpp
	g++ -c main.cpp       
nmiMeasure.o: nmiMeasure.hpp 
	g++ -c nmiMeasure.cpp
clean: 
	rm nmiMeasure  main.o nmiMeasure.o
