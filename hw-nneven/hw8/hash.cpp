#include<iostream>
#include "hash.h"
using namespace std;

unsigned int calculateHash(string mystring)
{
	/* add your code here */
	unsigned long long p = 0;
	for (int i = 0; i < (int)mystring.size(); i++)
	{
		p = (int)mystring[i] + (128 * p);
	}

	unsigned int w[4] = {0};
	w[3] = p % 65521;
	for (int i = 2; i >= 0; i--)
	{
		p = p / 65521;
		w[i] = p % 65521;
	}

	unsigned int result = (45912 * w[0] + 35511 * w[1] + 65169 * w[2] + 4625 * w[3]) % 65521;
	return result;
}
