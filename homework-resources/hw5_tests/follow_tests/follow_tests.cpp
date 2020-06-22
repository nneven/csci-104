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

TEST(Follow, CanFollow) 
{
	Handler* h = new FollowHandler();
	ASSERT_TRUE(h->canHandle("FOLLOW"));
	delete h;
}

TEST(Follow, NoFollowing)
{
	Handler* h = new FollowHandler(); 
	TwitEng twit; 
	twit.parse((char*)"twitterLarge2.dat"); 
	std::string command = "FOLLOW"; 
	std::stringstream s("Aaron Calvin"); 
	h->handle(&twit, command, s); 
	delete h; 
	twit.dumpFeeds(); 
	std::ifstream aaronFeed("Aaron.feed"); 
	ASSERT_FALSE(aaronFeed.fail()) << "Unable to open Aaron's main feed"; 
	std::string allText = getAllText(aaronFeed); 

	//Ensure all of Aaron's and Calvin's appropriate tweets are in Aaron's feed
	std::string timestamp = "2015-07-03 06:00:01"; 
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Aaron's main feed with timestamp " << timestamp;
	timestamp = "2015-07-03 06:00:54";
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Aaron's main feed with timestamp " << timestamp;
	timestamp = "2015-07-03 06:13:54";
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Aaron's main feed with timestamp " << timestamp;
}

TEST(Follow, HasFollowing) 
{
	Handler* h = new FollowHandler(); 
	TwitEng twit; 
	twit.parse((char*)"twitterLarge2.dat"); 
	std::string command = "FOLLOW"; 
	std::stringstream s("Calvin Emanuel"); 
	h->handle(&twit, command, s); 
	delete h; 
	twit.dumpFeeds(); 
	std::ifstream calvinFeed("Calvin.feed"); 
	ASSERT_FALSE(calvinFeed.fail()) << "Unable to open Calvin's main feed"; 
	std::string allText = getAllText(calvinFeed); 

	//Ensure appropriate tweets are in Calvin's feed
	std::string timestamp = "2015-07-03 06:04:35"; 
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Calvin's main feed with timestamp " << timestamp;
	timestamp = "2015-07-03 06:06:55"; 
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Calvin's main feed with timestamp " << timestamp;
	timestamp = "2015-07-03 06:13:54"; 
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Calvin's main feed with timestamp " << timestamp;
	timestamp = "2015-07-04 05:24:23"; 
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Calvin's main feed with timestamp " << timestamp;
	timestamp = "2015-07-04 05:08:58"; 
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Calvin's main feed with timestamp " << timestamp;
}

//Verify that new followers/following are being saved 
TEST(Follow, NoFollowingSave)
{
	// Follow
	Handler* h = new FollowHandler(); 
	TwitEng twit; 
	twit.parse((char*)"twitterLarge2.dat"); 
	std::string command = "FOLLOW"; 
	std::stringstream s("Aaron Calvin"); 
	h->handle(&twit, command, s); 
	delete h; 
	
	// Save
	h = new SaveHandler(); 
	command = "SAVE"; 
	std::stringstream ss("cs104_rocks.dat"); 
	h->handle(&twit, command, ss); 
	delete h; 

	TwitEng twitNew; 
	ASSERT_FALSE(twitNew.parse((char*)"cs104_rocks.dat")) << "Has a problem opening cs104_rocks.dat, which was where TwitEng should have saved the information"; 
	twitNew.dumpFeeds(); 
	std::ifstream aaronFeed("Aaron.feed"); 
	ASSERT_FALSE(aaronFeed.fail()) << "Unable to open Aaron's main feed"; 
	std::string allText = getAllText(aaronFeed); 

	//Ensure all of Aaron's and Calvin's appropriate tweets are in Aaron's feed
	std::string timestamp = "2015-07-03 06:00:01"; 
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Aaron's main feed with timestamp " << timestamp;
	timestamp = "2015-07-03 06:00:54";
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Aaron's main feed with timestamp " << timestamp;
	timestamp = "2015-07-03 06:13:54";
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Aaron's main feed with timestamp " << timestamp;
}

TEST(Follow, HasFollowingSave) 
{
	// Follow
	Handler* h = new FollowHandler(); 
	TwitEng twit; 
	twit.parse((char*)"twitterLarge2.dat"); 
	std::string command = "FOLLOW"; 
	std::stringstream s("Calvin Emanuel"); 
	h->handle(&twit, command, s); 
	delete h; 
	
	// Save
	h = new SaveHandler(); 
	command = "SAVE"; 
	std::stringstream ss("cs104_rocks.dat"); 
	h->handle(&twit, command, ss); 
	delete h;

	TwitEng twitNew; 
	ASSERT_FALSE(twitNew.parse((char*)"cs104_rocks.dat")) << "Has a problem opening cs104_rocks.dat, which was where TwitEng should have saved the information"; 
	twitNew.dumpFeeds();
	std::ifstream calvinFeed("Calvin.feed"); 
	ASSERT_FALSE(calvinFeed.fail()) << "Unable to open Calvin's main feed"; 
	std::string allText = getAllText(calvinFeed); 

	//Ensure appropriate tweets are in Calvin's feed
	std::string timestamp = "2015-07-03 06:04:35"; 
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Calvin's main feed with timestamp " << timestamp;
	timestamp = "2015-07-03 06:06:55"; 
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Calvin's main feed with timestamp " << timestamp;
	timestamp = "2015-07-03 06:13:54"; 
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Calvin's main feed with timestamp " << timestamp;
	timestamp = "2015-07-04 05:24:23"; 
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Calvin's main feed with timestamp " << timestamp;
	timestamp = "2015-07-04 05:08:58"; 
	ASSERT_FALSE(allText.find(timestamp) == std::string::npos) << "Tweet missing from Calvin's main feed with timestamp " << timestamp;
}