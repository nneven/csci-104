#include <iostream>
#include "hashtable.h"

using namespace std;

int main() {
	HashTable users(10);

	users.insert("Erika", 1);
	users.insert("Ruyan", 2);

	users.insert("Peter", 3);
	users.insert("Peter", 4);
	users.insert("Peter", 5);
	users.insert("Peter", 6);

	users.insert("Nikhil", 7);
	users.insert("Nisar", 8);
	users.insert("Aaron", 9);
	users.insert("Ashley", 10);
	users.insert("Mark", 11);
	users.insert("Kyle", 12);
	users.insert("Ellen", 13);

	cout << "Trying to find Arush:\t" << ( users.find("Arush") ? "BAD"  : "GOOD" ) << endl;
	cout << "Trying to find Peter:\t" << ( users.find("Peter") ? "GOOD" : "BAD"  ) << endl;
	cout << "Value correct:\t\t" <<  ( users.get("Peter") == 3 ? "GOOD" : "BAD"  ) << endl;
	cout << "Trying to find Mark:\t"  << ( users.find("Mark")  ? "GOOD" : "BAD"  ) << endl;
	cout << "Value correct:\t\t" <<  ( users.get("Mark") == 11 ? "GOOD" : "BAD"  ) << endl;
	cout << "Trying to find Erika:\t" << ( users.find("Erika") ? "GOOD" : "BAD"  ) << endl;
	cout << "Value correct:\t\t" <<  ( users.get("Erika") == 1 ? "GOOD" : "BAD"  ) << endl;

	users.insert("Arush", 14);
	cout << "Trying to find Arush:\t" << (users.find("Arush")  ? "GOOD" : "BAD"  ) << endl;
	cout << "Value correct:\t\t" << ( users.get("Arush") == 14 ? "GOOD" : "BAD"  ) << endl;

	users.remove("Peter");
	users.remove("Mark");
	cout << "Trying to find Peter:\t" << (users.find("Peter")  ? "BAD"  : "GOOD" ) << endl;
}