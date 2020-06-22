all: tests

tests: FORCE Array_Tests
	valgrind --leak-check=yes ./Array_Tests

FORCE: ;

Array_Tests: tests.cpp Array.o 
	g++ -Wall -std=c++11 -g Array.o tests.cpp -I /usr/include/gtest/ -l gtest -l gtest_main -pthread -o Array_Tests

Array.o: Array.h Array.cpp
	g++ -Wall -std=c++11 -g -c Array.cpp -o Array.o

clean:
	rm Array_Tests
	rm Array.o