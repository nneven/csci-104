CC = g++
CPPFLAGS = -g -Wall -std=c++11
BIN_DIR = bin
TEST_DIR = tests
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR) $(BIN_DIR)/DestructorTest $(BIN_DIR)/InsertNthTest $(BIN_DIR)/NthFromEndTest
	valgrind --leak-check=yes ./$(BIN_DIR)/DestructorTest
	valgrind --leak-check=yes ./$(BIN_DIR)/InsertNthTest
	valgrind --leak-check=yes ./$(BIN_DIR)/NthFromEndTest

$(BIN_DIR)/DestructorTest: $(BIN_DIR)/DestructorTest.o $(BIN_DIR)/LinkedList.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/DestructorTest.o: $(TEST_DIR)/DestructorTest.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/InsertNthTest: $(BIN_DIR)/InsertNthTest.o $(BIN_DIR)/LinkedList.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/InsertNthTest.o: $(TEST_DIR)/InsertNthTest.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/NthFromEndTest: $(BIN_DIR)/NthFromEndTest.o $(BIN_DIR)/LinkedList.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/NthFromEndTest.o: $(TEST_DIR)/NthFromEndTest.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/LinkedList.o: LinkedList.cpp LinkedList.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

$(TEST_DIR):
	mkdir $(TEST_DIR)

.phony: clean test

clean:
	-@rm -rf $(BIN_DIR)

DestructorTest: $(BIN_DIR) $(BIN_DIR)/DestructorTest
	valgrind --leak-check=yes ./$(BIN_DIR)/DestructorTest

InsertNthTest: $(BIN_DIR) $(BIN_DIR)/InsertNthTest
	valgrind --leak-check=yes ./$(BIN_DIR)/InsertNthTest

NthFromEndTest: $(BIN_DIR) $(BIN_DIR)/NthFromEndTest
	valgrind --leak-check=yes ./$(BIN_DIR)/NthFromEndTest
