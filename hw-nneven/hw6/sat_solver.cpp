#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <math.h>

using namespace std;

map<string, int> readExpression(char* filename, vector<vector<string> >& clauses)
{
	ifstream ifile(filename);
	string line;
	while (getline(ifile, line))
	{
		if (line != "" && line.front() != 'c' && line.front() != 'p' && line.front() != '%' && line.front() != '0')
		{
			vector<string> v;
			string variable;
			stringstream ss(line);
			while (ss >> variable)
			{
				if (variable != "0")
				{
					v.push_back(variable);
				}
			}
			clauses.push_back(v);
		}
	}

	map<string, int> variables;
	for (int i = 0; i < (int)clauses.size(); i++)
	{
		for (int j = 0; j < (int)clauses[i].size(); j++)
		{
			string key = clauses[i][j];
			if (key.front() == '-') key = key.substr(1);
			if (variables.find(key) == variables.end())
			{
				variables.insert(make_pair(key, 0));
			}	
		}
	}
	return variables;
}

void printMap(map<string, int> variables, ofstream& ofile)
{
	for (int i = 1; i <= (int)variables.size(); i++)
	{
		ofile << i << " = " << variables[to_string(i)] << endl;
	}
}

bool isValid(map<string, int> variables, vector<string> clause)
{
	for (int i = 0; i < (int)clause.size(); i++)
	{
		if (variables[clause[i]] == 1) return true;
		if (clause[i].front() == '-' && variables[clause[i].substr(1)] == 0) return true;
	}
	return false;
}

void solver(map<string, int> variables, vector<vector<string> > clauses, int vcount, int ccount, bool& solved, ofstream& ofile)
{	
	if (solved) return;
	if (vcount < (int)variables.size()) {
		vcount++;
		for (int i = 0; i < 2; i++)
		{
			if (variables.find(to_string(vcount)) != variables.end())
			{
				variables[to_string(vcount)] = i;
				solver(variables, clauses, vcount, ccount, solved, ofile);
			}
		}
	} else if (vcount == (int)variables.size()) {

		bool valid = true;
		for (int i = 0; i < (int)clauses.size(); i++)
		{
			// cout << i << " ";
			if (!isValid(variables, clauses[i]))
			{
				valid = false; 
				break;
			}
		}
		// cout << endl;
		if (valid)
		{
			printMap(variables, ofile);
			solved = true;
			// cout << "SOLVED" << endl;
		}
	}
}

int main(int argc, char* argv[])
{
  vector<vector<string> > clauses;

  // Parse the file
  map<string, int> variables = readExpression(argv[1], clauses);

  // Open the output file
  ofstream ofile(argv[2]);

  bool solved = false;
  solver(variables, clauses, 0, 0, solved, ofile);
  
  if (!solved) ofile << "No Solution" << endl;

  ofile.close();

  return 0;
}