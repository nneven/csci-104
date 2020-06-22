#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
	int x, count;
	ifstream ifile(argv[1]);
	ofstream ofile(argv[2]);
	ifile >> count;
	if (ifile.fail() || count == 0) ofile << 0;
	int *arr = new int[count];
	
	for (int i = 0; i < count; i++) {
		ifile >> x;
		arr[i] = x;
	}
	
	for (int i = 0; i < count / 2; i++) {
		ofile << arr[i] + arr[count - i - 1] << endl;
	}

	if (count % 2) ofile << arr[count / 2] * 2 << endl;
	
	delete[] arr;
	return 0;	
}