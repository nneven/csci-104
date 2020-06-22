all: remdup deque_test laundry

remdup: rem_dup.cpp rem_dup_lib.o
	g++ -g -Wall -std=c++11 rem_dup.cpp rem_dup_lib.o -o remdup

rem_dup_lib.o: rem_dup_lib.h rem_dup_lib.cpp
	g++ -g -Wall -c -std=c++11 rem_dup_lib.cpp -o rem_dup_lib.o

tests: FORCE deque_test
	valgrind --leak-check=yes ./deque_test

FORCE: ;

deque_test: deque_test.cpp deque.h
	g++ -Wall -std=c++11 -g deque.h deque_test.cpp -I /usr/include/gtest/ -l gtest -l gtest_main -pthread -o deque_test

deque.h:
	g++ -Wall -std=c++11 -g -c deque.h

laundry: laundry.cpp stack.h
	g++ -g -Wall -std=c++11 laundry.cpp stack.h -o laundry

stack.h:
	g++ -g -Wall -c -std=c++11 stack.h