#include "rem_dup_lib.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

void deleteAll(Item* head)
{
	while(head != nullptr)
	{
		Item* temp = head;
		head = head->next;
		delete temp;
	}
}

int main(int argc, char * argv[])
{
	int num;
	string line;
	ifstream ifile(argv[1]);

	// Read in list 1
	getline(ifile, line);
	stringstream ss(line);
	ss >> num;
	Item* head1 = new Item(num, nullptr);
	Item* temp = head1;
	while (ss >> num)
	{
		temp->next = new Item(num, nullptr);
		temp = temp->next;
	}

	// Read in list 2
	getline(ifile, line);
	stringstream ss2(line);
	ss2 >> num;
	Item* head2 = new Item(num, nullptr);
	temp = head2;
	while (ss2 >> num)
	{
		temp->next = new Item(num, nullptr);
		temp = temp->next;
	}

	// Recursive function calls
	removeConsecutive(head1);
	Item* head3 = concatenate(head1, head2);

	// List 3 file output
	ofstream ofile(argv[2]);
	temp = head3;
	while (temp != nullptr) {
		ofile << temp->val << " ";
		temp = temp->next;
	}
	ofile << endl;

	// Free memory
	deleteAll(head1);
	deleteAll(head2);
	deleteAll(head3);
	return 0;
}