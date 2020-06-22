#include <gtest/gtest.h>
#define protected public
#include <twiteng.h> 
#include <util.h>
#include <tweet.h>
#include <user.h>
#include <cmdhandler.h>
#include <iostream>
#include <fstream> 
#include <fstream>
#include <regex>

//Get all of the text from a particular file and return it as one string
std::string getAllText(std::ifstream& iFile)
{
	std::string result = ""; 
	std::string line; 

	while (std::getline(iFile, line)) {
		result += line; 
	}

	return result; 
}

TEST(Save, CanSave) 
{
	Handler* h = new SaveHandler();
	ASSERT_TRUE(h->canHandle("SAVE"));
	delete h;
}

TEST(Save, NoChanges)
{
	TwitEng twit, twit2;  
	twit.parse((char*)"twitterLarge2.dat"); 

	Handler* h = new SaveHandler(); 
	std::string command = "SAVE"; 
	std::stringstream s("cs104_rocks.dat"); 

	h->handle(&twit, command, s); 
	delete h; 

	std::ifstream cs104_rocks("cs104_rocks.dat"); 

	std::string allText = getAllText(cs104_rocks); 

	//make sure all user lines are present
	std::string line = "Aaron"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing the following user line: " << line; 
	line = "Bryan Calvin"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing the following user line: " << line; 
	line = "David Bryan Calvin"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing the following user line: " << line; 
	line = "Calvin Bryan"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing the following user line: " << line; 
	line = "Emanuel Bryan Calvin David";
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing the following user line: " << line; 

	line = "2015-07-03 06:00:01"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-03 06:00:54"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-03 06:04:35"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-03 06:06:55"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-03 06:13:54"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-04 05:24:23"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-03 06:19:04"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-03 06:33:33"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-04 05:08:58"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
}

TEST(Save, AddTweet)
{
	TwitEng twit; 
	DateTime dt; 
	twit.parse((char*)"twitterLarge2.dat"); 
	twit.addTweet("Aaron", dt, "Kilroy was here");
	Handler* h = new SaveHandler(); 
	std::string command = "SAVE"; 
	std::stringstream s("cs104_rocks.dat"); 
	h->handle(&twit, command, s); 
	delete h; 

	std::ifstream savedFile("cs104_rocks.dat"); 

	std::string allText = getAllText(savedFile); 

	std::string line = "Aaron"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing the following user line: " << line; 
	line = "Bryan Calvin"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing the following user line: " << line; 
	line = "David Bryan Calvin"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing the following user line: " << line; 
	line = "Calvin Bryan"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing the following user line: " << line; 
	line = "Emanuel Bryan Calvin David";
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing the following user line: " << line; 

	line = "2015-07-03 06:00:01"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-03 06:00:54"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-03 06:04:35"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-03 06:06:55"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-03 06:13:54"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-04 05:24:23"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-03 06:19:04"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-03 06:33:33"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 
	line = "2015-07-04 05:08:58"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet with timestamp: " << line; 

	line = "Kilroy was here"; 
	ASSERT_FALSE(allText.find(line) == std::string::npos) << "Missing tweet containing text: " << line; 
}
