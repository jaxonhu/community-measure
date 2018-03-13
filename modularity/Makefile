# Makefile

modularity:  main.o modularity.o
	g++ main.o modularity.o -lm -o modularity

main.o: modularity.hpp 
	g++ -c main.cpp

modularity.o: modularity.hpp
	g++ -c modularity.cpp

clean:
	rm -rf *.o modularity 
