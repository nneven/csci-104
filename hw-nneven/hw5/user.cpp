#include "user.h"
using namespace std;

User::User(string name)
{
	this->uname = name;
}

User::~User()
{
	for (list<Tweet*>::iterator it = utweets.begin(); it != utweets.end(); ++it)
	{
		// delete *it;
	}
}

string User::name() const
{
	return uname;
}

set<User*> User::followers() const
{
	return ufollowers;
}

set<User*> User::following() const
{
	return ufollowing;
}

list<Tweet*> User::tweets() const
{
	return utweets;
}

void User::addFollower(User* u)
{
	ufollowers.insert(u);
}

void User::addFollowing(User* u)
{
	ufollowing.insert(u);
}

void User::addTweet(Tweet* t)
{
	utweets.push_back(t);
}

void User::addFeed(Tweet *t)
{
	feed.push_back(t);
}

void User::addMention(Tweet* t)
{
	mentions.push_back(t);
}

vector<Tweet*> User::getFeed()
{
	for (set<User*>::iterator it = ufollowing.begin(); it != ufollowing.end(); ++it)
	{
		list<Tweet*> utweets = (*it)->tweets();
		feed.insert(feed.begin(), utweets.begin(), utweets.end());
	}
	for (vector<Tweet*>::iterator it = mentions.begin(); it != mentions.end(); ++it)
	{
		User* u = (*it)->user();
		if (ufollowing.find(u) != ufollowing.end()) feed.push_back(*it);
	}
	sort(feed.begin(), feed.end(), TweetComp());
	return feed;
}

vector<Tweet*> User::getMentions()
{
	return mentions;
}


bool User::operator<(const User& other) const
{
	return this->uname < other.uname;
}