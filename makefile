start: main.o source.o
	g++ main.o locminreinsert.o -o gotest

main.o: main.cpp
	g++ -c main.cpp

source.o: locminreinsert.cpp locminreinsert.h
	g++ -c locminreinsert.cpp

go:
	clear
	./gotest
	rm *.o
	rm gotest
	ls
