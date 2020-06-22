#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
	int count = 0;
	bool isDuplicate = false;
	vector<string> users, hashtags;
	ifstream ifile(argv[1]);
	if (ifile.fail()) cout << "Input file error" << endl;
	string word, line;
	while (getline(ifile, line)) {
		stringstream ss (line);
		if (line != "") count++;

		while (ss >> word) {
			
			if (word[0] == '@') {
				word = word.substr(1);
				for (int i = 0; i < (int)users.size(); i++) {
					if (users[i] == word) isDuplicate = true;
				}
				if (!isDuplicate) users.push_back(word);
				
			} else if (word[0] == '#') {
				word = word.substr(1);
				for (int i = 0; i < (int)hashtags.size(); i++) {
					if (hashtags[i] == word) isDuplicate = true;
				}
				if (!isDuplicate) hashtags.push_back(word);
			}

			isDuplicate = false;
		}
	}
	
	cout << "1. Number of tweets=" << count << endl;
	cout << "2. Unique users" << endl;
	for (int i = 0; i < (int)users.size(); i++) {
		cout << users[i] << endl;
	}
	cout << "3. Unique hashtags" << endl;
	for (int i = 0; i < (int)hashtags.size(); i++) {
		cout << hashtags[i] << endl;
	}
	
	return 0;
}