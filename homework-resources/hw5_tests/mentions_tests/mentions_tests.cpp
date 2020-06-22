#include <gtest/gtest.h>
#define protected public
#include "../../twiteng.h" 
#include "../../util.h"
#include "../../tweet.h"
#include "../../user.h"
#include "../../cmdhandler.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>

// 2015-07-03 06:00:01 Aaron I do not follow anyone, 
// and no one follows me therefore this should only appear in Aarons main feed
TEST(Mentions, NoFollowers)
{
	TwitEng te; 
	te.parse((char*)"twitterLarge2.dat"); 

	te.dumpFeeds(); 

	std::ifstream bryanFeed("Bryan.feed"); 
	std::ifstream bryanMentions("Bryan.mentions"); 

	std::ifstream aaronFeed("Aaron.feed"); 
	std::ifstream aaronMentions("Aaron.mentions"); 

	std::ifstream calvinFeed("Calvin.feed"); 
	std::ifstream calvinMentions("Calvin.mentions"); 

	std::ifstream emanuelFeed("Emanuel.feed"); 
	std::ifstream emanuelMentions("Emanuel.mentions"); 

	std::ifstream davidFeed("David.feed"); 
	std::ifstream davidMentions("David.mentions"); 

	ASSERT_FALSE(bryanFeed.fail()) << "Unable to open Bryan's main feed"; 
	ASSERT_FALSE(bryanMentions.fail()) << "Unable to open Bryan's mentions feed"; 

	ASSERT_FALSE(aaronFeed.fail()) << "Unable to open Aaron's main feed"; 
	ASSERT_FALSE(aaronMentions.fail()) << "Unable to open Aaron's mentions feed"; 

	ASSERT_FALSE(calvinFeed.fail()) << "Unable to open Calvin's main feed"; 
	ASSERT_FALSE(calvinMentions.fail()) << "Unable to open Calvin's mentions feed";

	ASSERT_FALSE(emanuelFeed.fail()) << "Unable to open Emanuel's main feed"; 
	ASSERT_FALSE(emanuelMentions.fail()) << "Unable to open Emanuel's mentions feed"; 

	ASSERT_FALSE(davidFeed.fail()) << "Unable to open David's main feed"; 
	ASSERT_FALSE(davidMentions.fail()) << "Unable to open David's mentions feed"; 

	std::string bryanAllMain = ""; 
	std::string bryanAllMentions = ""; 

	std::string aaronAllMain = ""; 
	std::string aaronAllMentions = ""; 

	std::string calvinAllMain = ""; 
	std::string calvinAllMentions = ""; 

	std::string emanuelAllMain = ""; 
	std::string emanuelAllMentions = ""; 

	std::string davidAllMain = ""; 
	std::string davidAllMentions = ""; 

	std::string line; 

	while (std::getline(bryanFeed, line)) bryanAllMain += line; 
	while (std::getline(bryanMentions, line)) bryanAllMentions += line;

	while (std::getline(aaronFeed, line)) aaronAllMain += line; 
	while (std::getline(aaronMentions, line)) aaronAllMentions += line;

	while (std::getline(emanuelFeed, line)) emanuelAllMain += line; 
	while (std::getline(emanuelMentions, line)) emanuelAllMentions += line;

	while (std::getline(calvinFeed, line)) calvinAllMain += line; 
	while (std::getline(calvinMentions, line)) calvinAllMentions += line;

	while (std::getline(davidFeed, line)) davidAllMain += line; 
	while (std::getline(davidMentions, line)) davidAllMentions += line; 

	std::string tweet = "2015-07-03 06:00:01 Aaron I do not follow anyone, and no one follows me therefore this should only appear in Aarons main feed";

	ASSERT_TRUE(bryanAllMain.find(tweet) == std::string::npos) << "Aaron's tweet should not be in Bryan's main feed"; 
	ASSERT_TRUE(bryanAllMentions.find(tweet) == std::string::npos) << "Aaron's tweet should not be in Bryan.mentions"; 

	ASSERT_TRUE(calvinAllMain.find(tweet) == std::string::npos) << "Aaron's tweet should not be in Calvin's main feed"; 
	ASSERT_TRUE(calvinAllMentions.find(tweet) == std::string::npos) << "Aaron's tweet should not be in Calvin.mentions"; 

	ASSERT_TRUE(aaronAllMain.find(tweet) != std::string::npos) << "Was not able to locate Aaron's tweet in Aaron's main feed"; 
	ASSERT_TRUE(aaronAllMentions.find(tweet) == std::string::npos) << "Aaron's tweet should not be in Aaron.mentions"; 

	ASSERT_TRUE(emanuelAllMain.find(tweet) == std::string::npos) << "Aaron's tweet should not be in Emanuel's main feed"; 
	ASSERT_TRUE(emanuelAllMentions.find(tweet) == std::string::npos) << "Aaron's tweet should not be in Emanuel.mentions"; 

	ASSERT_TRUE(davidAllMain.find(tweet) == std::string::npos) << "Aaron's tweet should not be in David's main feed"; 
	ASSERT_TRUE(davidAllMentions.find(tweet) == std::string::npos) << "Aaron's tweet should not be in David.mentions"; 
}

// 2015-07-03 06:00:54 Aaron @Bryan This tweet should appear only in Aaron main feed and Bryan mention feed
TEST(Mentions, DirectMention) 
{
	TwitEng te; 
	te.parse((char*)"twitterLarge2.dat"); 

	te.dumpFeeds(); 

	std::ifstream bryanFeed("Bryan.feed"); 
	std::ifstream bryanMentions("Bryan.mentions"); 

	std::ifstream aaronFeed("Aaron.feed"); 
	std::ifstream aaronMentions("Aaron.mentions"); 

	std::ifstream calvinFeed("Calvin.feed"); 
	std::ifstream calvinMentions("Calvin.mentions"); 

	std::ifstream emanuelFeed("Emanuel.feed"); 
	std::ifstream emanuelMentions("Emanuel.mentions"); 

	std::ifstream davidFeed("David.feed"); 
	std::ifstream davidMentions("David.mentions"); 

	ASSERT_FALSE(bryanFeed.fail()) << "Unable to open Bryan's main feed"; 
	ASSERT_FALSE(bryanMentions.fail()) << "Unable to open Bryan's mentions feed"; 

	ASSERT_FALSE(aaronFeed.fail()) << "Unable to open Aaron's main feed"; 
	ASSERT_FALSE(aaronMentions.fail()) << "Unable to open Aaron's mentions feed"; 

	ASSERT_FALSE(calvinFeed.fail()) << "Unable to open Calvin's main feed"; 
	ASSERT_FALSE(calvinMentions.fail()) << "Unable to open Calvin's mentions feed";

	ASSERT_FALSE(emanuelFeed.fail()) << "Unable to open Emanuel's main feed"; 
	ASSERT_FALSE(emanuelMentions.fail()) << "Unable to open Emanuel's mentions feed"; 

	ASSERT_FALSE(davidFeed.fail()) << "Unable to open David's main feed"; 
	ASSERT_FALSE(davidMentions.fail()) << "Unable to open David's mentions feed"; 

	std::string bryanAllMain = ""; 
	std::string bryanAllMentions = ""; 

	std::string aaronAllMain = ""; 
	std::string aaronAllMentions = ""; 

	std::string calvinAllMain = ""; 
	std::string calvinAllMentions = ""; 

	std::string emanuelAllMain = ""; 
	std::string emanuelAllMentions = ""; 

	std::string davidAllMain = ""; 
	std::string davidAllMentions = ""; 

	std::string line; 

	while (std::getline(bryanFeed, line)) bryanAllMain += line; 
	while (std::getline(bryanMentions, line)) bryanAllMentions += line;

	while (std::getline(aaronFeed, line)) aaronAllMain += line; 
	while (std::getline(aaronMentions, line)) aaronAllMentions += line;

	while (std::getline(emanuelFeed, line)) emanuelAllMain += line; 
	while (std::getline(emanuelMentions, line)) emanuelAllMentions += line;

	while (std::getline(calvinFeed, line)) calvinAllMain += line; 
	while (std::getline(calvinMentions, line)) calvinAllMentions += line;

	while (std::getline(davidFeed, line)) davidAllMain += line; 
	while (std::getline(davidMentions, line)) davidAllMentions += line; 

	std::string tweet = "2015-07-03 06:00:54 Aaron @Bryan This tweet should appear only in Aaron main feed and Bryan mention feed";

	ASSERT_TRUE(bryanAllMain.find(tweet) == std::string::npos) << "Aaron's tweet should not be in Bryan's main feed"; 
	ASSERT_TRUE(bryanAllMentions.find(tweet) != std::string::npos) << "Unable to locate Aaron's tweet in Bryan.mentions"; 

	ASSERT_TRUE(calvinAllMain.find(tweet) == std::string::npos) << "Aaron's tweet should not be in Calvin's main feed"; 
	ASSERT_TRUE(calvinAllMentions.find(tweet) == std::string::npos) << "Aaron's tweet should not be in Calvin.mentions"; 

	ASSERT_TRUE(aaronAllMain.find(tweet) != std::string::npos) << "Was not able to locate Aaron's tweet in Aaron's main feed"; 
	ASSERT_TRUE(aaronAllMentions.find(tweet) == std::string::npos) << "Aaron's tweet should not be in Aaron.mentions"; 

	ASSERT_TRUE(emanuelAllMain.find(tweet) == std::string::npos) << "Aaron's tweet should not be in Emanuel's main feed"; 
	ASSERT_TRUE(emanuelAllMentions.find(tweet) == std::string::npos) << "Aaron's tweet should not be in Emanuel.mentions"; 

	ASSERT_TRUE(davidAllMain.find(tweet) == std::string::npos) << "Aaron's tweet should not be in David's main feed"; 
	ASSERT_TRUE(davidAllMentions.find(tweet) == std::string::npos) << "Aaron's tweet should not be in David.mentions"; 
}



/**
* Tweets without direction mention should still show up in appropriate
* main feeds
* 
* Calvin's tweet should only be in Bryan, Calvin, David, and Emanuel's main feeds
* 
* "2015-07-03 06:13:54 Calvin This tweet should appear 
* in my, Bryan, David, and Emanuel main feed"
*/
TEST(Mentions, NoMentions)
{
	TwitEng te; 
	te.parse((char*)"twitterLarge2.dat"); 

	te.dumpFeeds(); 

	std::ifstream bryanFeed("Bryan.feed"); 
	std::ifstream bryanMentions("Bryan.mentions"); 

	std::ifstream aaronFeed("Aaron.feed"); 
	std::ifstream aaronMentions("Aaron.mentions"); 

	std::ifstream calvinFeed("Calvin.feed"); 
	std::ifstream calvinMentions("Calvin.mentions"); 

	std::ifstream emanuelFeed("Emanuel.feed"); 
	std::ifstream emanuelMentions("Emanuel.mentions"); 

	std::ifstream davidFeed("David.feed"); 
	std::ifstream davidMentions("David.mentions"); 

	ASSERT_FALSE(bryanFeed.fail()) << "Unable to open Bryan's main feed"; 
	ASSERT_FALSE(bryanMentions.fail()) << "Unable to open Bryan's mentions feed"; 

	ASSERT_FALSE(aaronFeed.fail()) << "Unable to open Aaron's main feed"; 
	ASSERT_FALSE(aaronMentions.fail()) << "Unable to open Aaron's mentions feed"; 

	ASSERT_FALSE(calvinFeed.fail()) << "Unable to open Calvin's main feed"; 
	ASSERT_FALSE(calvinMentions.fail()) << "Unable to open Calvin's mentions feed";

	ASSERT_FALSE(emanuelFeed.fail()) << "Unable to open Emanuel's main feed"; 
	ASSERT_FALSE(emanuelMentions.fail()) << "Unable to open Emanuel's mentions feed"; 

	ASSERT_FALSE(davidFeed.fail()) << "Unable to open David's main feed"; 
	ASSERT_FALSE(davidMentions.fail()) << "Unable to open David's mentions feed"; 

	std::string bryanAllMain = ""; 
	std::string bryanAllMentions = ""; 

	std::string aaronAllMain = ""; 
	std::string aaronAllMentions = ""; 

	std::string calvinAllMain = ""; 
	std::string calvinAllMentions = ""; 

	std::string emanuelAllMain = ""; 
	std::string emanuelAllMentions = ""; 

	std::string davidAllMain = ""; 
	std::string davidAllMentions = "";  

	std::string line; 

	while (std::getline(bryanFeed, line)) bryanAllMain += line; 
	while (std::getline(bryanMentions, line)) bryanAllMentions += line;

	while (std::getline(aaronFeed, line)) aaronAllMain += line; 
	while (std::getline(aaronMentions, line)) aaronAllMentions += line;

	while (std::getline(emanuelFeed, line)) emanuelAllMain += line; 
	while (std::getline(emanuelMentions, line)) emanuelAllMentions += line;

	while (std::getline(calvinFeed, line)) calvinAllMain += line; 
	while (std::getline(calvinMentions, line)) calvinAllMentions += line;

	while (std::getline(davidFeed, line)) davidAllMain += line; 
	while (std::getline(davidMentions, line)) davidAllMentions += line; 

	std::string tweet = "2015-07-03 06:13:54 Calvin This tweet should appear in my, Bryan, David, and Emmanuel main feed";

	ASSERT_TRUE(bryanAllMain.find(tweet) != std::string::npos) << "Was not able to locate Calvin's tweet in Bryan's main feed"; 
	ASSERT_TRUE(bryanAllMentions.find(tweet) == std::string::npos) << "Calvin's tweet should not be in Bryan.mentions"; 

	ASSERT_TRUE(calvinAllMain.find(tweet) != std::string::npos) << "Was not able to locate Calvin's tweet in Calvin's main feed"; 
	ASSERT_TRUE(calvinAllMentions.find(tweet) == std::string::npos) << "Calvin's tweet should not be in Calvin.mentions"; 

	ASSERT_TRUE(aaronAllMain.find(tweet) == std::string::npos) << "Calvin's tweet should not be in Aaron.feed"; 
	ASSERT_TRUE(aaronAllMentions.find(tweet) == std::string::npos) << "Calvin's tweet should not be in Aaron.mentions"; 

	ASSERT_TRUE(emanuelAllMain.find(tweet) != std::string::npos) << "Was not able to locate Calvin's tweet in Emanuel's main feed"; 
	ASSERT_TRUE(emanuelAllMentions.find(tweet) == std::string::npos) << "Calvin's tweet should not be in Emanuel.mentions"; 

	ASSERT_TRUE(davidAllMain.find(tweet) != std::string::npos) << "Was not able to locate Calvin's tweet in David's main feed"; 
	ASSERT_TRUE(davidAllMentions.find(tweet) == std::string::npos) << "Calvin's tweet should not be in David.mentions"; 
}

/**
* Tweets without direct mentions but with indirect mentions should be in 
* appropriate mention feeds
*
* Bryan's tweet should be in mention feed of Aaron
* and main feed of Bryan, Calvin, David, and Emanuel
* 
* "2015-07-03 06:06:55 Bryan This tweet should appear 
* in @Aaron mention feed, and in Bryan, Calvin, David, and Emanuel main feed"
*/
TEST(Mentions, IndirectMentions)
{
	TwitEng te; 
	te.parse((char*)"twitterLarge2.dat"); 

	te.dumpFeeds(); 

	std::ifstream bryanFeed("Bryan.feed"); 
	std::ifstream bryanMentions("Bryan.mentions"); 

	std::ifstream aaronFeed("Aaron.feed"); 
	std::ifstream aaronMentions("Aaron.mentions"); 

	std::ifstream calvinFeed("Calvin.feed"); 
	std::ifstream calvinMentions("Calvin.mentions"); 

	std::ifstream emanuelFeed("Emanuel.feed"); 
	std::ifstream emanuelMentions("Emanuel.mentions"); 

	std::ifstream davidFeed("David.feed"); 
	std::ifstream davidMentions("David.mentions"); 

	ASSERT_FALSE(bryanFeed.fail()) << "Unable to open Bryan's main feed"; 
	ASSERT_FALSE(bryanMentions.fail()) << "Unable to open Bryan's mentions feed"; 

	ASSERT_FALSE(aaronFeed.fail()) << "Unable to open Aaron's main feed"; 
	ASSERT_FALSE(aaronMentions.fail()) << "Unable to open Aaron's mentions feed"; 

	ASSERT_FALSE(calvinFeed.fail()) << "Unable to open Calvin's main feed"; 
	ASSERT_FALSE(calvinMentions.fail()) << "Unable to open Calvin's mentions feed";

	ASSERT_FALSE(emanuelFeed.fail()) << "Unable to open Emanuel's main feed"; 
	ASSERT_FALSE(emanuelMentions.fail()) << "Unable to open Emanuel's mentions feed"; 

	ASSERT_FALSE(davidFeed.fail()) << "Unable to open David's main feed"; 
	ASSERT_FALSE(davidMentions.fail()) << "Unable to open David's mentions feed"; 

	std::string bryanAllMain = ""; 
	std::string bryanAllMentions = ""; 

	std::string aaronAllMain = ""; 
	std::string aaronAllMentions = ""; 

	std::string calvinAllMain = ""; 
	std::string calvinAllMentions = ""; 

	std::string emanuelAllMain = ""; 
	std::string emanuelAllMentions = ""; 

	std::string davidAllMain = ""; 
	std::string davidAllMentions = ""; 

	std::string line; 

	while (std::getline(bryanFeed, line)) bryanAllMain += line; 
	while (std::getline(bryanMentions, line)) bryanAllMentions += line;

	while (std::getline(aaronFeed, line)) aaronAllMain += line; 
	while (std::getline(aaronMentions, line)) aaronAllMentions += line;

	while (std::getline(emanuelFeed, line)) emanuelAllMain += line; 
	while (std::getline(emanuelMentions, line)) emanuelAllMentions += line;

	while (std::getline(calvinFeed, line)) calvinAllMain += line; 
	while (std::getline(calvinMentions, line)) calvinAllMentions += line;

	while (std::getline(davidFeed, line)) davidAllMain += line; 
	while (std::getline(davidMentions, line)) davidAllMentions += line; 

	std::string tweet = "2015-07-03 06:06:55 Bryan This tweet should appear in @Aaron mention feed, and in Bryan, Calvin, David, and Emmanuel main feed";

	ASSERT_TRUE(bryanAllMain.find(tweet) != std::string::npos) << "Was not able to locate Bryan's tweet in Bryan's main feed"; 
	ASSERT_TRUE(bryanAllMentions.find(tweet) == std::string::npos) << "Bryan's tweet should not be in Bryan.mentions"; 

	ASSERT_TRUE(calvinAllMain.find(tweet) != std::string::npos) << "Was not able to locate Bryan's tweet in Calvin's main feed"; 
	ASSERT_TRUE(calvinAllMentions.find(tweet) == std::string::npos) << "Bryan's tweet should not be in Calvin.mentions"; 

	ASSERT_TRUE(aaronAllMain.find(tweet) == std::string::npos) << "Bryan's tweet should not be in Aaron's main feed"; 
	ASSERT_TRUE(aaronAllMentions.find(tweet) != std::string::npos) << "Unable to locate Bryan's tweet in Aaron.mentions"; 

	ASSERT_TRUE(emanuelAllMain.find(tweet) != std::string::npos) << "Was not able to locate Bryan's tweet in Emanuel's main feed"; 
	ASSERT_TRUE(emanuelAllMentions.find(tweet) == std::string::npos) << "Bryan's tweet should not be in Emanuel.mentions"; 

	ASSERT_TRUE(davidAllMain.find(tweet) != std::string::npos) << "Was not able to locate Bryan's tweet in David's main feed"; 
	ASSERT_TRUE(davidAllMentions.find(tweet) == std::string::npos) << "Bryan's tweet should not be in David.mentions"; 
}

/**
* Tweets with direct mentions should not show up in main feeds of followers
* 
* Bryan's tweet should not be in David or Emanuel's main feeds
* 
* "2015-07-03 06:04:35 Bryan @Calvin This tweet should appear in 
* Calvin main and mention feeds, and in my main feed"
*/
TEST(Mentions, UsersFollowEachOther) 
{
	TwitEng te; 
	te.parse((char*)"twitterLarge2.dat"); 

	te.dumpFeeds(); 

	std::ifstream bryanFeed("Bryan.feed"); 
	std::ifstream bryanMentions("Bryan.mentions"); 

	std::ifstream aaronFeed("Aaron.feed"); 
	std::ifstream aaronMentions("Aaron.mentions"); 

	std::ifstream calvinFeed("Calvin.feed"); 
	std::ifstream calvinMentions("Calvin.mentions"); 

	std::ifstream emanuelFeed("Emanuel.feed"); 
	std::ifstream emanuelMentions("Emanuel.mentions"); 

	std::ifstream davidFeed("David.feed"); 
	std::ifstream davidMentions("David.mentions"); 

	ASSERT_FALSE(bryanFeed.fail()) << "Unable to open Bryan's main feed"; 
	ASSERT_FALSE(bryanMentions.fail()) << "Unable to open Bryan's mentions feed"; 

	ASSERT_FALSE(aaronFeed.fail()) << "Unable to open Aaron's main feed"; 
	ASSERT_FALSE(aaronMentions.fail()) << "Unable to open Aaron's mentions feed"; 

	ASSERT_FALSE(calvinFeed.fail()) << "Unable to open Calvin's main feed"; 
	ASSERT_FALSE(calvinMentions.fail()) << "Unable to open Calvin's mentions feed";

	ASSERT_FALSE(emanuelFeed.fail()) << "Unable to open Emanuel's main feed"; 
	ASSERT_FALSE(emanuelMentions.fail()) << "Unable to open Emanuel's mentions feed"; 

	ASSERT_FALSE(davidFeed.fail()) << "Unable to open David's main feed"; 
	ASSERT_FALSE(davidMentions.fail()) << "Unable to open David's mentions feed"; 

	std::string bryanAllMain = ""; 
	std::string bryanAllMentions = ""; 

	std::string aaronAllMain = ""; 
	std::string aaronAllMentions = ""; 

	std::string calvinAllMain = ""; 
	std::string calvinAllMentions = ""; 

	std::string emanuelAllMain = ""; 
	std::string emanuelAllMentions = ""; 

	std::string davidAllMain = ""; 
	std::string davidAllMentions = "";  

	std::string line; 

	while (std::getline(bryanFeed, line)) bryanAllMain += line; 
	while (std::getline(bryanMentions, line)) bryanAllMentions += line;

	while (std::getline(aaronFeed, line)) aaronAllMain += line; 
	while (std::getline(aaronMentions, line)) aaronAllMentions += line;

	while (std::getline(emanuelFeed, line)) emanuelAllMain += line; 
	while (std::getline(emanuelMentions, line)) emanuelAllMentions += line;

	while (std::getline(calvinFeed, line)) calvinAllMain += line; 
	while (std::getline(calvinMentions, line)) calvinAllMentions += line;

	while (std::getline(davidFeed, line)) davidAllMain += line; 
	while (std::getline(davidMentions, line)) davidAllMentions += line; 

	std::string tweet = "2015-07-03 06:04:35 Bryan @Calvin This tweet should appear in Calvin main and mention feeds, and in my main feed";

	ASSERT_TRUE(bryanAllMain.find(tweet) != std::string::npos) << "Was not able to locate Bryan's tweet in Bryan's main feed"; 
	ASSERT_TRUE(bryanAllMentions.find(tweet) == std::string::npos) << "Bryan's tweet should not be in Bryan.mentions"; 

	ASSERT_TRUE(calvinAllMain.find(tweet) != std::string::npos) << "Was not able to locate Bryan's tweet in Calvin's main feed"; 
	ASSERT_TRUE(calvinAllMentions.find(tweet) != std::string::npos) << "Was not able to locate Bryan's tweet in Calvin.mentions"; 

	ASSERT_TRUE(aaronAllMain.find(tweet) == std::string::npos) << "Bryan's tweet should not be in Aaron's main feed"; 
	ASSERT_TRUE(aaronAllMentions.find(tweet) == std::string::npos) << "Bryan's tweet should not be in Aaron.mentions"; 

	ASSERT_TRUE(emanuelAllMain.find(tweet) == std::string::npos) << "Bryan's tweet should not be in Emanuel's main feed"; 
	ASSERT_TRUE(emanuelAllMentions.find(tweet) == std::string::npos) << "Bryan's tweet should not be in Emanuel.mentions"; 

	ASSERT_TRUE(davidAllMain.find(tweet) == std::string::npos) << "Bryan's tweet should not be in David's main feed"; 
	ASSERT_TRUE(davidAllMentions.find(tweet) == std::string::npos) << "Bryan's tweet should not be in David.mentions"; 
}

/**
* Any indirect mentions with direct mentions should not be seen in 
* either of the indirect mentionee's feeds
* 
* Tweet by Emanuel only appears in Emanuel's main and Bryan's mentions
* but not in either of Aaron's feeds
* 
* "2015-07-03 06:33:33 Emanuel @Bryan I am sure @Aaron can not see this"
*/
TEST(Mentions, DirectAndIndirectMentions)
{
	TwitEng te; 
	te.parse((char*)"twitterLarge2.dat"); 

	te.dumpFeeds(); 

	std::ifstream bryanFeed("Bryan.feed"); 
	std::ifstream bryanMentions("Bryan.mentions"); 

	std::ifstream aaronFeed("Aaron.feed"); 
	std::ifstream aaronMentions("Aaron.mentions"); 

	std::ifstream calvinFeed("Calvin.feed"); 
	std::ifstream calvinMentions("Calvin.mentions"); 

	std::ifstream emanuelFeed("Emanuel.feed"); 
	std::ifstream emanuelMentions("Emanuel.mentions"); 

	std::ifstream davidFeed("David.feed"); 
	std::ifstream davidMentions("David.mentions"); 

	ASSERT_FALSE(bryanFeed.fail()) << "Unable to open Bryan's main feed"; 
	ASSERT_FALSE(bryanMentions.fail()) << "Unable to open Bryan's mentions feed"; 

	ASSERT_FALSE(aaronFeed.fail()) << "Unable to open Aaron's main feed"; 
	ASSERT_FALSE(aaronMentions.fail()) << "Unable to open Aaron's mentions feed"; 

	ASSERT_FALSE(calvinFeed.fail()) << "Unable to open Calvin's main feed"; 
	ASSERT_FALSE(calvinMentions.fail()) << "Unable to open Calvin's mentions feed";

	ASSERT_FALSE(emanuelFeed.fail()) << "Unable to open Emanuel's main feed"; 
	ASSERT_FALSE(emanuelMentions.fail()) << "Unable to open Emanuel's mentions feed"; 

	ASSERT_FALSE(davidFeed.fail()) << "Unable to open David's main feed"; 
	ASSERT_FALSE(davidMentions.fail()) << "Unable to open David's mentions feed"; 

	std::string bryanAllMain = ""; 
	std::string bryanAllMentions = ""; 

	std::string aaronAllMain = ""; 
	std::string aaronAllMentions = ""; 

	std::string calvinAllMain = ""; 
	std::string calvinAllMentions = ""; 

	std::string emanuelAllMain = ""; 
	std::string emanuelAllMentions = ""; 

	std::string davidAllMain = ""; 
	std::string davidAllMentions = ""; 

	std::string line; 

	while (std::getline(bryanFeed, line)) bryanAllMain += line; 
	while (std::getline(bryanMentions, line)) bryanAllMentions += line;

	while (std::getline(aaronFeed, line)) aaronAllMain += line; 
	while (std::getline(aaronMentions, line)) aaronAllMentions += line;

	while (std::getline(emanuelFeed, line)) emanuelAllMain += line; 
	while (std::getline(emanuelMentions, line)) emanuelAllMentions += line;

	while (std::getline(calvinFeed, line)) calvinAllMain += line; 
	while (std::getline(calvinMentions, line)) calvinAllMentions += line;

	while (std::getline(davidFeed, line)) davidAllMain += line; 
	while (std::getline(davidMentions, line)) davidAllMentions += line; 

	std::string tweet = "2015-07-03 06:33:33 Emanuel @Bryan I am sure @Aaron can not see this"; 

	ASSERT_TRUE(bryanAllMain.find(tweet) == std::string::npos) << "Emanuel's tweet should not be in Bryan's main feed"; 
	ASSERT_TRUE(bryanAllMentions.find(tweet) != std::string::npos) << "Was not able to locate Emanuel's tweet in Bryan.mentions";

	ASSERT_TRUE(calvinAllMain.find(tweet) == std::string::npos) << "Emanuel's tweet should not be in Calvin's main feed";
	ASSERT_TRUE(calvinAllMentions.find(tweet) == std::string::npos) << "Emmanuel's tweet should not be in Calvin.mentions"; 

	ASSERT_TRUE(aaronAllMain.find(tweet) == std::string::npos) << "Emanuel's tweet should not be in Aaron's main feed"; 
	ASSERT_TRUE(aaronAllMentions.find(tweet) == std::string::npos) << "Emanuel's tweet should not be in Aaron.mentions"; 

	ASSERT_TRUE(emanuelAllMain.find(tweet) != std::string::npos) << "Was not able to locate Emanuel's tweet in Emanuel's main feed"; 
	ASSERT_TRUE(emanuelAllMentions.find(tweet) == std::string::npos) << "Emanuel's tweet should not be in Emanuel.mentions"; 

	ASSERT_TRUE(davidAllMain.find(tweet) == std::string::npos) << "Emanuel's tweet should not be in David's main feed"; 
	ASSERT_TRUE(davidAllMentions.find(tweet) == std::string::npos) << "Emanuel's tweet should not be in David.mentions"; 
}

// 2015-07-04 05:24:23 Calvin @Bryan can see this tweet in his main and mention feeds
TEST(Mentions, TweetInMainAndMention) 
{
	TwitEng te; 
	te.parse((char*)"twitterLarge2.dat"); 

	te.dumpFeeds(); 

	std::ifstream bryanFeed("Bryan.feed"); 
	std::ifstream bryanMentions("Bryan.mentions"); 

	std::ifstream aaronFeed("Aaron.feed"); 
	std::ifstream aaronMentions("Aaron.mentions"); 

	std::ifstream calvinFeed("Calvin.feed"); 
	std::ifstream calvinMentions("Calvin.mentions"); 

	std::ifstream emanuelFeed("Emanuel.feed"); 
	std::ifstream emanuelMentions("Emanuel.mentions"); 

	std::ifstream davidFeed("David.feed"); 
	std::ifstream davidMentions("David.mentions"); 

	ASSERT_FALSE(bryanFeed.fail()) << "Unable to open Bryan's main feed"; 
	ASSERT_FALSE(bryanMentions.fail()) << "Unable to open Bryan's mentions feed"; 

	ASSERT_FALSE(aaronFeed.fail()) << "Unable to open Aaron's main feed"; 
	ASSERT_FALSE(aaronMentions.fail()) << "Unable to open Aaron's mentions feed"; 

	ASSERT_FALSE(calvinFeed.fail()) << "Unable to open Calvin's main feed"; 
	ASSERT_FALSE(calvinMentions.fail()) << "Unable to open Calvin's mentions feed";

	ASSERT_FALSE(emanuelFeed.fail()) << "Unable to open Emanuel's main feed"; 
	ASSERT_FALSE(emanuelMentions.fail()) << "Unable to open Emanuel's mentions feed"; 

	ASSERT_FALSE(davidFeed.fail()) << "Unable to open David's main feed"; 
	ASSERT_FALSE(davidMentions.fail()) << "Unable to open David's mentions feed"; 

	std::string bryanAllMain = ""; 
	std::string bryanAllMentions = ""; 

	std::string aaronAllMain = ""; 
	std::string aaronAllMentions = ""; 

	std::string calvinAllMain = ""; 
	std::string calvinAllMentions = ""; 

	std::string emanuelAllMain = ""; 
	std::string emanuelAllMentions = ""; 

	std::string davidAllMain = ""; 
	std::string davidAllMentions = ""; 

	std::string line; 

	while (std::getline(bryanFeed, line)) bryanAllMain += line; 
	while (std::getline(bryanMentions, line)) bryanAllMentions += line;

	while (std::getline(aaronFeed, line)) aaronAllMain += line; 
	while (std::getline(aaronMentions, line)) aaronAllMentions += line;

	while (std::getline(emanuelFeed, line)) emanuelAllMain += line; 
	while (std::getline(emanuelMentions, line)) emanuelAllMentions += line;

	while (std::getline(calvinFeed, line)) calvinAllMain += line; 
	while (std::getline(calvinMentions, line)) calvinAllMentions += line;

	while (std::getline(davidFeed, line)) davidAllMain += line; 
	while (std::getline(davidMentions, line)) davidAllMentions += line; 

	std::string tweet = "2015-07-04 05:24:23 Calvin @Bryan can see this tweet in his main and mention feeds"; 

	ASSERT_TRUE(bryanAllMain.find(tweet) != std::string::npos) << "Was not able to locate Calvin's tweet in Bryan's main feed"; 
	ASSERT_TRUE(bryanAllMentions.find(tweet) != std::string::npos) << "Was not able to locate Calvin's tweet in Bryan.mentions";

	ASSERT_TRUE(calvinAllMain.find(tweet) != std::string::npos) << "Was not able to locate Calvin's tweet in Calvin's main feed";
	ASSERT_TRUE(calvinAllMentions.find(tweet) == std::string::npos) << "Calvin's tweet should not be in Calvin.mentions"; 

	ASSERT_TRUE(aaronAllMain.find(tweet) == std::string::npos) << "Calvin's tweet should not be in Aaron's main feed"; 
	ASSERT_TRUE(aaronAllMentions.find(tweet) == std::string::npos) << "Calvin's tweet should not be in Aaron.mentions"; 

	ASSERT_TRUE(emanuelAllMain.find(tweet) == std::string::npos) << "Calvin's tweet should not be in Emanuel's main feed"; 
	ASSERT_TRUE(emanuelAllMentions.find(tweet) == std::string::npos) << "Calvin's tweet should not be in Emanuel.mentions"; 

	ASSERT_TRUE(davidAllMain.find(tweet) == std::string::npos) << "Calvin's tweet should not be in David's main feed"; 
	ASSERT_TRUE(davidAllMentions.find(tweet) == std::string::npos) << "Calvin's tweet should not be in David.mentions"; 
}

// 2015-07-03 06:19:04 David @Bryan Only Bryan can see this in his mention feed and I should see it in my main feed
TEST(Mentions, DirectMentionNotFollowingBack)
{
	TwitEng te; 
	te.parse((char*)"twitterLarge2.dat"); 

	te.dumpFeeds(); 

	std::ifstream bryanFeed("Bryan.feed"); 
	std::ifstream bryanMentions("Bryan.mentions"); 

	std::ifstream aaronFeed("Aaron.feed"); 
	std::ifstream aaronMentions("Aaron.mentions"); 

	std::ifstream calvinFeed("Calvin.feed"); 
	std::ifstream calvinMentions("Calvin.mentions"); 

	std::ifstream emanuelFeed("Emanuel.feed"); 
	std::ifstream emanuelMentions("Emanuel.mentions"); 

	std::ifstream davidFeed("David.feed"); 
	std::ifstream davidMentions("David.mentions"); 

	ASSERT_FALSE(bryanFeed.fail()) << "Unable to open Bryan's main feed"; 
	ASSERT_FALSE(bryanMentions.fail()) << "Unable to open Bryan's mentions feed"; 

	ASSERT_FALSE(aaronFeed.fail()) << "Unable to open Aaron's main feed"; 
	ASSERT_FALSE(aaronMentions.fail()) << "Unable to open Aaron's mentions feed"; 

	ASSERT_FALSE(calvinFeed.fail()) << "Unable to open Calvin's main feed"; 
	ASSERT_FALSE(calvinMentions.fail()) << "Unable to open Calvin's mentions feed";

	ASSERT_FALSE(emanuelFeed.fail()) << "Unable to open Emanuel's main feed"; 
	ASSERT_FALSE(emanuelMentions.fail()) << "Unable to open Emanuel's mentions feed"; 

	ASSERT_FALSE(davidFeed.fail()) << "Unable to open David's main feed"; 
	ASSERT_FALSE(davidMentions.fail()) << "Unable to open David's mentions feed"; 

	std::string bryanAllMain = ""; 
	std::string bryanAllMentions = ""; 

	std::string aaronAllMain = ""; 
	std::string aaronAllMentions = ""; 

	std::string calvinAllMain = ""; 
	std::string calvinAllMentions = ""; 

	std::string emanuelAllMain = ""; 
	std::string emanuelAllMentions = ""; 

	std::string davidAllMain = ""; 
	std::string davidAllMentions = ""; 

	std::string line; 

	while (std::getline(bryanFeed, line)) bryanAllMain += line; 
	while (std::getline(bryanMentions, line)) bryanAllMentions += line;

	while (std::getline(aaronFeed, line)) aaronAllMain += line; 
	while (std::getline(aaronMentions, line)) aaronAllMentions += line;

	while (std::getline(emanuelFeed, line)) emanuelAllMain += line; 
	while (std::getline(emanuelMentions, line)) emanuelAllMentions += line;

	while (std::getline(calvinFeed, line)) calvinAllMain += line; 
	while (std::getline(calvinMentions, line)) calvinAllMentions += line;

	while (std::getline(davidFeed, line)) davidAllMain += line; 
	while (std::getline(davidMentions, line)) davidAllMentions += line; 

	std::string tweet = "2015-07-03 06:19:04 David @Bryan Only Bryan can see this in his mention feed and I should see it in my main feed"; 

	ASSERT_TRUE(bryanAllMain.find(tweet) == std::string::npos) << "David's tweet should not be in Bryan's main feed"; 
	ASSERT_TRUE(bryanAllMentions.find(tweet) != std::string::npos) << "Was not able to locate David's tweet in Bryan.mentions";

	ASSERT_TRUE(calvinAllMain.find(tweet) == std::string::npos) << "David's tweet should not be in Calvin's main feed";
	ASSERT_TRUE(calvinAllMentions.find(tweet) == std::string::npos) << "David's tweet should not be in Calvin.mentions"; 

	ASSERT_TRUE(aaronAllMain.find(tweet) == std::string::npos) << "David's tweet should not be in Aaron's main feed"; 
	ASSERT_TRUE(aaronAllMentions.find(tweet) == std::string::npos) << "David's tweet should not be in Aaron.mentions"; 

	ASSERT_TRUE(emanuelAllMain.find(tweet) == std::string::npos) << "David's tweet should not be in Emanuel's main feed"; 
	ASSERT_TRUE(emanuelAllMentions.find(tweet) == std::string::npos) << "David's tweet should not be in Emanuel.mentions"; 

	ASSERT_TRUE(davidAllMain.find(tweet) != std::string::npos) << "Was not able to locate David's tweet in David's main feed"; 
	ASSERT_TRUE(davidAllMentions.find(tweet) == std::string::npos) << "David's tweet should not be in David.mentions"; 
}

// 2015-07-04 05:08:58 Emanuel @Calvin This one should not show up in any feed of @Bryan
TEST(Mentions, NoneOfBryansFeeds) 
{
	TwitEng te; 
	te.parse((char*)"twitterLarge2.dat"); 

	te.dumpFeeds(); 

	std::ifstream bryanFeed("Bryan.feed"); 
	std::ifstream bryanMentions("Bryan.mentions"); 

	std::ifstream aaronFeed("Aaron.feed"); 
	std::ifstream aaronMentions("Aaron.mentions"); 

	std::ifstream calvinFeed("Calvin.feed"); 
	std::ifstream calvinMentions("Calvin.mentions"); 

	std::ifstream emanuelFeed("Emanuel.feed"); 
	std::ifstream emanuelMentions("Emanuel.mentions"); 

	std::ifstream davidFeed("David.feed"); 
	std::ifstream davidMentions("David.mentions"); 

	ASSERT_FALSE(bryanFeed.fail()) << "Unable to open Bryan's main feed"; 
	ASSERT_FALSE(bryanMentions.fail()) << "Unable to open Bryan's mentions feed"; 

	ASSERT_FALSE(aaronFeed.fail()) << "Unable to open Aaron's main feed"; 
	ASSERT_FALSE(aaronMentions.fail()) << "Unable to open Aaron's mentions feed"; 

	ASSERT_FALSE(calvinFeed.fail()) << "Unable to open Calvin's main feed"; 
	ASSERT_FALSE(calvinMentions.fail()) << "Unable to open Calvin's mentions feed";

	ASSERT_FALSE(emanuelFeed.fail()) << "Unable to open Emanuel's main feed"; 
	ASSERT_FALSE(emanuelMentions.fail()) << "Unable to open Emanuel's mentions feed"; 

	ASSERT_FALSE(davidFeed.fail()) << "Unable to open David's main feed"; 
	ASSERT_FALSE(davidMentions.fail()) << "Unable to open David's mentions feed"; 

	std::string bryanAllMain = ""; 
	std::string bryanAllMentions = ""; 

	std::string aaronAllMain = ""; 
	std::string aaronAllMentions = ""; 

	std::string calvinAllMain = ""; 
	std::string calvinAllMentions = ""; 

	std::string emanuelAllMain = ""; 
	std::string emanuelAllMentions = ""; 

	std::string davidAllMain = ""; 
	std::string davidAllMentions = ""; 

	std::string line; 

	while (std::getline(bryanFeed, line)) bryanAllMain += line; 
	while (std::getline(bryanMentions, line)) bryanAllMentions += line;

	while (std::getline(aaronFeed, line)) aaronAllMain += line; 
	while (std::getline(aaronMentions, line)) aaronAllMentions += line;

	while (std::getline(emanuelFeed, line)) emanuelAllMain += line; 
	while (std::getline(emanuelMentions, line)) emanuelAllMentions += line;

	while (std::getline(calvinFeed, line)) calvinAllMain += line; 
	while (std::getline(calvinMentions, line)) calvinAllMentions += line;

	while (std::getline(davidFeed, line)) davidAllMain += line; 
	while (std::getline(davidMentions, line)) davidAllMentions += line; 

	std::string tweet = "2015-07-04 05:08:58 Emanuel @Calvin This one should not show up in any feed of @Bryan"; 

	ASSERT_TRUE(bryanAllMain.find(tweet) == std::string::npos) << "Emanuel's tweet should not be in Bryan's main feed"; 
	ASSERT_TRUE(bryanAllMentions.find(tweet) == std::string::npos) << "Emanuel's tweet should not be in Bryan.mentions";
}
