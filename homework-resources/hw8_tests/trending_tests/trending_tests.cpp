#include <gtest/gtest.h>
#include <string>
#include <user_code_runner.h>
#include <kwsys/SystemTools.hxx>
#include <fstream>
#include <stdio.h>
#include <stack>
#include <set>
#include <map>
#include "tagdata.h"
#include <queue>
#include <algorithm>
using namespace std;

string getStudentOutput(string testName, string database, string commands, bool useValgrind)
{
	string executablePath = TRENDING_EXECUTABLE;
	string testFolder = TEST_BINARY_DIR "/trending_tests/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	string databaseFilePath = testFolder + "/database.txt";
	string inputCommandFilePath = testFolder + "/command.txt";
	string outputFilePath = testFolder +"/output.txt";
	string stdoutFilePath = testFolder + "/stdout.txt";

	//write input to file
	ofstream inputWriter(databaseFilePath);
	inputWriter << database;
	inputWriter.flush();

	UserCodeRunner runner(testFolder, executablePath, {databaseFilePath}, stdoutFilePath, useValgrind);
	runner.setStdin(commands, inputCommandFilePath);
	runner.execute();
	
	return stdoutFilePath;
}

priority_queue<TagData> parseInput(string input)
{
	map<string, TagData> tagmap;
	priority_queue<TagData> q;
	stringstream ss(input);
	string line;
	while(getline(ss, line))
	{
		stringstream ss2(line);
		while(getline(ss2, line, '#'))
		{
			string tag;
			ss2 >> tag;
			if(tag != "")
			{
				if(tagmap.find(tag) == tagmap.end())
				{
					TagData data(tag, 1);
					tagmap.insert(make_pair(tag, data));
					
				}
				else
				{
					tagmap.find(tag)->second.num += 1;
				}
			}
		}
	}
	for(auto it = tagmap.begin(); it != tagmap.end(); ++it)
	{
		q.push(it->second);
	}
	return q;
}

void printQueue(priority_queue<TagData> q)
{
	while(!q.empty())
	{
		q.pop();
	}
}

string correctOutput(priority_queue<TagData> q, int num)
{
	string output;
	int prevFreq = -1;
	for(int i = 0; i < num && !q.empty(); i++)
	{
		
		output += q.top().tag + " : " + to_string(q.top().num) + "\n";
		prevFreq = q.top().num;
		q.pop();
		if(i + 1 == num && prevFreq == q.top().num) // Correct Output contains extras if there are ties, so that order doesn't matter
		{
			i--;
		}
	}
	return output;
}

int numEntries(string mentionsList)
{
	stringstream ss(mentionsList);
	string line;
	int count = 0;
	while(getline(ss, line))
	{
		if(line != "" && line != "\n" && line != " ")
		{
			count++;
		}
	}
	return count;
}

bool isSorted(string studentOutput)
{
	stringstream ss(studentOutput);
	string line;
	vector<int> mentions;
	while(getline(ss, line))
	{
		stringstream ss2(line);
		string temp;
		getline(ss2, temp, ':');
		int num;
		ss2 >> num;
	}
	return is_sorted(mentions.begin(), mentions.end(), greater<int>());
}

TagData parseLineOfOutput(string line)
{
	stringstream ss(line);
	string mention;
	getline(ss, mention, ':');
	int num;
	ss >> num;
	TagData tag(mention, num);
	return tag;
}

bool outputsMatch(string correctOutput, string studentOutput)
{
	string line;
	stringstream ss(correctOutput);
	map<string, TagData> tagMap;
	while(getline(ss, line))
	{
		TagData data = parseLineOfOutput(line);
		if(data.tag != "" || data.tag != "\n" || data.tag != " ")
			tagMap.insert(make_pair(data.tag, data));
	}	
	stringstream ss2(studentOutput);
	while(getline(ss2, line))
	{
		TagData data = parseLineOfOutput(line);
		if(data.tag == "" || data.tag == "\n" || data.tag == " ")
			continue;
		if(tagMap.find(data.tag) == tagMap.end()) // not in correct output
		{
			return false;
		}
		if(tagMap.find(data.tag)->second.num != data.num) // not same number of mentions
		{
			return false;
		}
	}
	return true;
}

testing::AssertionResult compareResults(string correctOutput, string studentOutput, int num)
{
	
	// output contains correct number of entries
	if(numEntries(studentOutput) != num && numEntries(studentOutput) != numEntries(correctOutput))
	{
		return testing::AssertionFailure() << "Incorrect number of entries, expected " << num << " parsed from output file " << numEntries(studentOutput) << endl;
	}
	// output is sorted by mentions
	if(!isSorted(studentOutput))
	{
		return testing::AssertionFailure() << "Entries are not sorted" << endl;
	}
	//Checks that every entry in student output is in correct output
	if(!outputsMatch(correctOutput, studentOutput))
	{
		return testing::AssertionFailure() << "There are elements in student output that do not match elements in the correct output";
	}

	return testing::AssertionSuccess();
}

testing::AssertionResult checkCodeSingleTrend(string testName, string input, string commands, int num)
{
	string outputFile = getStudentOutput(testName, input, commands, true);
	ifstream inputWriter(outputFile);
  string output((istreambuf_iterator<char>(inputWriter)), (istreambuf_iterator<char>()) );
	output = output.substr(output.find("Enter command:") + 16); 
	output = output.substr(0, output.find("Enter command:"));
	priority_queue<TagData> q = parseInput(input + "\n" + commands);
	string corr = correctOutput(q, num);
	return compareResults(corr, output, num);
}

testing::AssertionResult checkCodeWithTweets(string testName, string input, string commands, int num)
{
	string outputFile = getStudentOutput(testName, input, commands, true);
	ifstream inputWriter(outputFile);
  string output((istreambuf_iterator<char>(inputWriter)), (istreambuf_iterator<char>()) );
	output = output.substr(output.find("Enter command:") + 16); 
	stringstream ss(output);
	string line;
	while(getline(ss, line))
	{	
		if(line != "" && line != "\n" && line != " " && line.find("Enter") == string::npos && line.find("Login") == string::npos && line.find("login") == string::npos)
		{
			break;
		}
	}
	
	output = line + "\n";
	while(getline(ss, line))
	{
		output += line +"\n";
	}
	priority_queue<TagData> q = parseInput(input + "\n" + commands);
	string corr = correctOutput(q, num);
	output = output.substr(0, output.find("Enter command:"));
	return compareResults(corr, output, num);

}

TEST(Trending, ParseOnlyNominal)
{
	string input = 
	"1\n"
	"Eric 28114\n"
	"2019-01-01 12:34:56 Eric #a\n"
	"2019-01-01 12:34:56 Eric #a #b\n"
	"2019-01-01 12:34:56 Eric #a #b #c\n"
	"2019-01-01 12:34:56 Eric #a #b #c #d\n";
	auto q = parseInput(input);
	string commands =
	"TRENDING 3\n"
	"QUIT\n";
	int num = 3;
	ASSERT_TRUE(checkCodeSingleTrend("ParseOnly", input, commands, num));
}

TEST(Trending, ParseOnlyAllTweets)
{
	string input = 
	"1\n"
	"Eric 28114\n"
	"2019-01-01 12:34:56 Eric #a\n"
	"2019-01-01 12:34:56 Eric #a #b\n"
	"2019-01-01 12:34:56 Eric #a #b #c\n"
	"2019-01-01 12:34:56 Eric #a #b #c #d\n";
	auto q = parseInput(input);
	string commands =
	"TRENDING 4\n"
	"QUIT\n";
	int num = 4;
	ASSERT_TRUE(checkCodeSingleTrend("ParseOnlyAllTweets", input, commands, num));
}

TEST(Trending, ParseOnlyOverNumTweets)
{
	string input = 
	"1\n"
	"Eric 28114\n"
	"2019-01-01 12:34:56 Eric #a\n"
	"2019-01-01 12:34:56 Eric #a #b\n"
	"2019-01-01 12:34:56 Eric #a #b #c\n"
	"2019-01-01 12:34:56 Eric #a #b #c #d\n";
	auto q = parseInput(input);
	string commands =
	"TRENDING 100\n"
	"QUIT\n";
	int num = 100;
	ASSERT_TRUE(checkCodeSingleTrend("ParseOnlyOverNumTweets", input, commands, num));
}

TEST(Trending, MultiTweetersNominal)
{
	string input = 
	"2\n"
	"Eric 28114\n"
	"Sean 12345\n"
	"2019-01-01 12:34:56 Eric #a\n"
	"2019-01-01 12:34:56 Sean #a #b\n"
	"2019-01-01 12:34:56 Eric #a #b #c\n"
	"2019-01-01 12:34:56 Sean #a #b #c #d\n";
	auto q = parseInput(input);
	string commands =
	"TRENDING 3\n"
	"QUIT\n";
	int num = 3;
	ASSERT_TRUE(checkCodeSingleTrend("MultiTweetersNominal", input, commands, num));
}

TEST(Trending, MultiTweetersAllTweets)
{
	string input = 
	"2\n"
	"Eric 28114\n"
	"Sean 12345\n"
	"2019-01-01 12:34:56 Eric #a\n"
	"2019-01-01 12:34:56 Sean #a #b\n"
	"2019-01-01 12:34:56 Eric #a #b #c\n"
	"2019-01-01 12:34:56 Sean #a #b #c #d\n";
	auto q = parseInput(input);
	string commands =
	"TRENDING 4\n"
	"QUIT\n";
	int num = 4;
	ASSERT_TRUE(checkCodeSingleTrend("MultiUserAllTweets", input, commands, num));
}

TEST(Trending, MultiTweetersOverNumTweets)
{
	string input = 
	"2\n"
	"Eric 28114\n"
	"Sean 11234\n"
	"2019-01-01 12:34:56 Eric #a\n"
	"2019-01-01 12:34:56 Sean #a #b\n"
	"2019-01-01 12:34:56 Eric #a #b #c\n"
	"2019-01-01 12:34:56 Sean #a #b #c #d\n";
	auto q = parseInput(input);
	string commands =
	"TRENDING 100\n"
	"QUIT\n";
	int num = 100;
	ASSERT_TRUE(checkCodeSingleTrend("MultiUserAllTweets", input, commands, num));
}


TEST(Trending, NegativeRequest)
{
	string input = 
	"2\n"
	"Eric 28114\n"
	"Sean 11234\n"
	"2019-01-01 12:34:56 Eric #a\n"
	"2019-01-01 12:34:56 Sean #a #b\n"
	"2019-01-01 12:34:56 Eric #a #b #c\n"
	"2019-01-01 12:34:56 Sean #a #b #c #d\n";
	auto q = parseInput(input);
	string commands =
	"TRENDING -1\n"
	"QUIT\n";
	string outputFile = getStudentOutput("NegativeRequest", input, commands, true);
	ifstream inputWriter(outputFile);
  string output((istreambuf_iterator<char>(inputWriter)), (istreambuf_iterator<char>()) );
	output = output.substr(output.find("Enter command:") + 16); 
	output = output.substr(0, output.find("Enter command:"));
	ASSERT_TRUE(output.find(':') == string::npos);
}

TEST(Trending, DuplicateHashTagInSameTweet)
{
	string input = 
	"1\n"
	"Eric 12345\n"
	"2019-01-01 12:34:56 Eric #tag #tag";

	string commands =
	"TRENDING 1\n"
	"QUIT\n";
	
	string outputFile = getStudentOutput("Duplicate", input, commands, true);
	ifstream inputWriter(outputFile);
  string output((istreambuf_iterator<char>(inputWriter)), (istreambuf_iterator<char>()) );
	output = output.substr(output.find("Enter command:") + 16); 
	output = output.substr(0, output.find("Enter command:"));
	
	stringstream ss(output);
	int num; string line;
	getline(ss, line, ':');
	ss >> num;
	ASSERT_EQ(1, num);
}

TEST(Trending, UpdateHashtag)
{
	string input = 
	"2\n"
	"Eric 28114\n"
	"Sean 11234\n"
	"2019-01-01 12:34:56 Eric #a\n"
	"2019-01-01 12:34:56 Sean #a #b\n"
	"2019-01-01 12:34:56 Eric #a #b #c\n"
	"2019-01-01 12:34:56 Sean #a #b #c #d\n";
	auto q = parseInput(input);
	string commands =
	"Login Eric abc123\n"
	"Tweet Eric #a #c\n"
	"Tweet Eric #a #d\n"
	"Trending 3\n"
	"QUIT\n";
	
	ASSERT_TRUE(checkCodeWithTweets("UpdateHashTag", input, commands, 3));
}

TEST(Trending, UpdateHashtag2)
{
	string input = 
	"2\n"
	"Eric 28114\n"
	"Sean 11234\n"
	"2019-01-01 12:34:56 Eric #a\n"
	"2019-01-01 12:34:56 Sean #a #b\n"
	"2019-01-01 12:34:56 Eric #a #b #c\n"
	"2019-01-01 12:34:56 Sean #a #b #c #d\n";
	auto q = parseInput(input);
	string commands =
	"Login Eric abc123\n"
	"Tweet Eric #a #c\n"
	"Tweet Eric #c #d\n"
	"Tweet Eric #c #e\n"
	"Tweet Eric #e #c\n"
	"Trending 3\n"
	"QUIT\n";
	
	ASSERT_TRUE(checkCodeWithTweets("UpdateHashTag2", input, commands, 3));

}

TEST(Trending, UpdateHashtag3)
{
	string input = 
	"2\n"
	"Eric 28114\n"
	"Sean 11234\n"
	"2019-01-01 12:34:56 Eric #a\n"
	"2019-01-01 12:34:56 Sean #a #b\n"
	"2019-01-01 12:34:56 Eric #a #b #c\n"
	"2019-01-01 12:34:56 Sean #a #b #c #d\n";
	auto q = parseInput(input);
	string commands =
	"Login Eric abc123\n"
	"Tweet Eric #e #d\n"
	"Tweet Eric #c #e\n"
	"Tweet Eric #a #e\n"
	"Tweet Eric #e #b\n"
	"Tweet Eric #e #f\n"
	"Trending 3\n"
	"QUIT\n";
	
	ASSERT_TRUE(checkCodeWithTweets("UpdateHashTag3", input, commands, 3));

}

TEST(Trending, TwoCalls)
{
	string input = 
	"2\n"
	"Eric 28114\n"
	"Sean 11234\n"
	"2019-01-01 12:34:56 Eric #a\n"
	"2019-01-01 12:34:56 Sean #a #b\n"
	"2019-01-01 12:34:56 Eric #a #b #c\n"
	"2019-01-01 12:34:56 Sean #a #b #c #d\n";
	auto q = parseInput(input);
	string commands =
	"Trending 3\n"
	"Trending 3\n"
	"QUIT\n";

	string outputFile = getStudentOutput("TwoCalls", input, commands, true);
	ifstream inputWriter(outputFile);
  string output((istreambuf_iterator<char>(inputWriter)), (istreambuf_iterator<char>()) );
	output = output.substr(output.find("Enter command:") + 16);
	string secondOutput = output.substr(output.find("Enter command:") + 16);
	output = output.substr(0, output.find("Enter command:"));
	secondOutput = secondOutput.substr(0, secondOutput.find("Enter command:"));
	ASSERT_TRUE(outputsMatch(output, secondOutput));
}
