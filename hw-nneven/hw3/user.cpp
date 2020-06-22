#include "user.h"
using namespace std;

User::User(string name)
{
	this->uname = name;
	ufollowers = new set<User*>;
	ufollowing = new set<User*>;
	utweets = new list<Tweet*>;
	feed = new vector<Tweet*>;
}

User::~User()
{
	delete ufollowers;
	delete ufollowing;
	for (list<Tweet*>::iterator it = utweets->begin(); it != utweets->end(); ++it)
	{
		delete *it;
	}
	delete utweets;
	delete feed;
}

string User::name() const
{
	return uname;
}

set<User*> User::followers() const
{
	return *ufollowers;
}

set<User*> User::following() const
{
	return *ufollowing;
}

list<Tweet*> User::tweets() const
{
	return *utweets;
}

void User::addFollower(User* u)
{
	ufollowers->insert(u);
}

void User::addFollowing(User* u)
{
	ufollowing->insert(u);
}

void User::addTweet(Tweet* t)
{
	utweets->push_back(t);
	feed->push_back(t);
}

vector<Tweet*> User::getFeed()
{
	for (set<User*>::iterator it = ufollowing->begin(); it != ufollowing->end(); ++it)
	{
		list<Tweet*> utweets = (*it)->tweets();
		feed->insert(feed->begin(), utweets.begin(), utweets.end());
	}
	sort(feed->begin(), feed->end(), TweetComp());
	return *feed;
}


bool User::operator<(const User& other) const
{
	return this->uname < other.uname;
}