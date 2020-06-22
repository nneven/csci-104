#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "stack.h"
using namespace std;

int main(int argc, char* argv[])
{
	int num;
	string line;
	Stack<string> dirty;
	ifstream ifile(argv[1]);
	ofstream ofile(argv[2]);
	while (ifile >> num)
	{
		if (num == 0) {
			dirty.push("black");
		} else if (num == -1) {
			dirty.push("white");
		} else if (num > 0) {
			// Employee laundry pickup output
			if (num > (int)dirty.size()) num = dirty.size();
			for (int i = 0; i < num; i++) {
				ofile << dirty.top() << " ";
				dirty.pop();
			}
			ofile << endl;
		}
	}
}