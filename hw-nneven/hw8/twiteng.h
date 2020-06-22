#ifndef TWITENG_H
#define TWITENG_H
#include <map>
#include <string>
#include <set>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "tweet.h"
#include "user.h"
#include "datetime.h"
#include "util.h"
#include "heap.h"
#include "hsort.h"
#include "tagdata.h"
#include "hash.h"

class TwitEng
{
	public:
	TwitEng();
	~TwitEng();
	/**
	* Parses the Twitter database and populates internal structures
	* @param filename of the database file
	* @return true if there is an error, false if successful
	*/
	bool parse(char* filename);
	
	/**
	* Allocates a tweet from its parts and adds it to internal structures
	* @param username of the user who made the tweet
	* @param timestamp of the tweet
	* @param text is the actual text of the tweet as a single string
	*/
	void addTweet(const std::string& username, const DateTime& time, const std::string& text);
	
	void addFollow(const std::string& username, const std::string& following);

	/**
	* Searches for tweets with the given words and strategy
	* @param words is the hashtag terms in any case without the '#'
	* @param strategy 0=AND, 1=OR
	* @return the tweets that match the search
	*/
	std::vector<Tweet*> search(std::vector<std::string>& terms, int strategy);
	
	/**
	* Dump feeds of each user to their own file
	*/
	void dumpFeeds();

	void dumpMentions();

	void saveData(const std::string& filename);

	void tarjan(const std::string& filename);

	void trending(int n);

	bool login(std::string name, std::string password);

	void logout();

	User* getActiveUser();
	
	/* You may add other member functions */

	private:

	/* Add any other data members or helper functions here  */

	User* active;
	std::map<std::string, User*> users;
	std::set<Tweet*> allTweets;
	std::map<std::string, std::set<Tweet*> > hashtags;
	Heap<TagData, TagStringEqual, TagIntGreater, TagStringHasher> popular;

	void strongConnect(int index, User* u, std::stack<User*>& s, int& count, std::ofstream& ofile);
};

#endif
