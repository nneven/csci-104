#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void readWords(char* filename, vector<vector<string> >& words);

// client interface
void generateSentences(vector<vector<string> >& words, ofstream& ofile);

// recursive helper function
void genHelper(vector<vector<string> >& words,
	       ofstream& ofile,
	       int currentOption,
	       string sentence,
	       int& numSentences);

void readWords(char* filename,vector<vector<string> >& words)
{
	ifstream ifile(filename);
	for (int i = 0; i < 5; i++)
	{
		string word, line;
		vector<string> result;
		getline(ifile, line);
		stringstream ss(line);
		while (ss >> word)
		{
			result.push_back(word);
		}
		words.push_back(result);
	}
}

void generateSentences(vector<vector<string> >& words, ofstream& ofile)
{
	int total = 0;
	genHelper(words, ofile, 0, "", total);
	ofile << total << " " << "sentences." << endl;
}

void genHelper(vector<vector<string> >& words,
	       ofstream& ofile,
	       int currentOption,
	       string sentence,
	       int& numSentences)
{
	if (currentOption == 0)
	{
		sentence = "The";
		genHelper(words, ofile, 1, sentence, numSentences);
	} else if (currentOption == 1) {
		genHelper(words, ofile, 2, sentence, numSentences);
		for (int i = 0; i < (int)words[0].size(); i++)
		{
			genHelper(words, ofile, 2, sentence + " " + words[0][i], numSentences);
		}
	} else if (currentOption == 2) {
		for (int i = 0; i < (int)words[1].size(); i++)
		{
			genHelper(words, ofile, 3, sentence + " " + words[1][i], numSentences);
		}
	} else if (currentOption == 3) {
		for (int i = 0; i < (int)words[2].size(); i++)
		{
			genHelper(words, ofile, 4, sentence + " " + words[2][i], numSentences);
		}
	} else {
		numSentences++;
		ofile << sentence << "." << endl;
		for (int i = 0; i < (int)words[3].size(); i++)
		{
			numSentences++;
			ofile << sentence << " " << words[3][i] << "." << endl;
		}
	}
}

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Usage ./sentences input_file output_file" << endl;
  }
  vector<vector<string> > words;

  // Parse the file
  readWords(argv[1], words);

  // Check the status of parsing
  if(words.size() < 4){
    cerr << "Input file requires 4 lines of words" << endl;
    return 1;
  }

  // Open the output file
  ofstream ofile(argv[2]);
 
  // generate all the sentence options writing them to ofile
  generateSentences(words, ofile);

  ofile.close();

  return 0;
}
