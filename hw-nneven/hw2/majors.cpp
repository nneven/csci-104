#include <map>
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctype.h>
#include "setops.h"
using namespace std;

// Takes in a string and returns an ALL CAPS version
string toUpperCase(string word)
{
	for (int i = 0; i < (int)word.size(); i++)
	{
		word[i] = toupper((char)word[i]);
	}
	return word;
}

int main(int argc, char* argv[])
{
	ifstream ifile(argv[1]);
	set<string> majors, names;
	map<string, set<string> > result;
	if (ifile.fail()) cout << "Input file error" << endl;
	string line;

	// Creates map of Majors (keys) to set of Names (values)
	while (getline(ifile, line, ',')) {
		stringstream ss(line);
		string word, name, major;
		ss >> name;

		// Process names
		while (ss >> word) {
			name += (" " + word);
		}
		getline(ifile, line);
		stringstream ss2(line);

		// Process majors
		while (ss2 >> word) {
			major = toUpperCase(word);
			majors.insert(major);
		}

		// Creates set and map
		for (set<string>::iterator itr = majors.begin(); itr != majors.end(); ++itr)
		{
			map<string, set<string> >::iterator itr2 = result.find(*itr);
			if (itr2 == result.end()) {
				names.insert(name);
				result.insert(make_pair(*itr, names));
			} else itr2->second.insert(name);
		}
		majors.clear();
		names.clear();
	}

	// Processes command file and creates output file from map
	ifstream cmdfile(argv[2]);
	ofstream ofile(argv[3]); // edit
	while (getline(cmdfile, line))
	{
		stringstream ss(line);
		ofile << line << endl;
		cout << line << endl;
		string major;
		int count = 0;
		while (ss >> major) {
			major = toUpperCase(major);
			count++;
			if (count > 1)
			{
				names = names & result[major];
			} else names = result[major];
		}
		for (set<string>::iterator itr = names.begin(); itr != names.end(); ++itr)
		{
			ofile << *itr << endl;
			cout << *itr << endl;
		}
		ofile << endl; // edit
		cout << endl;
		majors.clear();
		names.clear();
	}
	return 0;
}
