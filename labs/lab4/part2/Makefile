all: tests

tests: FORCE Matrix_Tests
	valgrind --leak-check=yes ./Matrix_Tests

FORCE: ;

Matrix_Tests: tests.cpp Matrix.o 
	g++ -Wall -std=c++11 -g Matrix.o tests.cpp -I /usr/include/gtest/ -l gtest -l gtest_main -pthread -o Matrix_Tests

Matrix.o: Matrix.h Matrix.cpp
	g++ -Wall -std=c++11 -g -c Matrix.cpp -o Matrix.o

clean:
	rm Matrix_Tests
	rm Matrix.o