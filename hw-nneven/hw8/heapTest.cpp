#include <iostream>
#include <vector>
#include <string>
#include "heap.h"

using namespace std;

void printAll(Heap<int> h, string message)
{
	cout << message << endl;
	while (!h.empty())
	{
		cout << h.top() << endl;
		h.pop();
	}
}
int main()
{
	Heap<int> test;
	test.push(2);
	// test.push(1);
	test.push(8);
	test.push(5);
	test.push(3);
	test.push(4);
	test.push(9);
	test.push(7);
	test.push(6);

	printAll(test, "Test");

	// test.decreaseKey(9, 10);
	test.decreaseKey(9, 1);

	printAll(test, "Test");

	return 0;
}