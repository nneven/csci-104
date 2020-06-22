#include <iostream>
#include <vector>
#include <string>
#include "hsort.h"

using namespace std;

void printAll(vector<int> v, string message)
{
	cout << message << endl;
	for (int i = 0; i < (int)v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl << endl;
}
int main()
{
	vector<int> list;
	list.push_back(2);
	list.push_back(1);
	list.push_back(8);
	list.push_back(5);
	list.push_back(3);
	list.push_back(4);
	list.push_back(9);
	list.push_back(7);
	list.push_back(6);
	vector<int> test = list;

	printAll(list, "Original");
	hsort(test, greater<int>());
	printAll(test, "Greater");
	hsort(test, less<int>());
	printAll(test, "Less");

	return 0;
}