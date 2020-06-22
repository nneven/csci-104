#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

/**
Hash Table for CS104 lab 13. Only stores strings.
*/
class HashTable {
public:
	HashTable(int);
	~HashTable();

	void  insert(std::string key, int value);
	bool  find(std::string key);
	void  remove(std::string key);
	int   get(std::string key);

private:
	std::vector<std::pair<std::string, int>>* data;
	int size;
};

#endif