all: majors

majors: majors.cpp setops.o
	g++ -g -Wall majors.cpp setops.o -o majors

setops.o: setops.h setops.cpp
	g++ -g -Wall -c setops.cpp -o setops.o