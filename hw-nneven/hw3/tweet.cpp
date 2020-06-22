#include "tweet.h"
#include "util.h"
using namespace std;

Tweet::Tweet()
{

}

Tweet::Tweet(User* user, const DateTime& time, const string& text)
{
	this->tuser = user;
	this->dtime = time;
	this->post = text;
	this->htags = new set<string>;
	string word;
	stringstream ss(post);
	while (ss >> word)
	{	
		convLower(word);
		if (word[0] == '#') htags->insert(word.substr(1));
	}
}

Tweet::~Tweet()
{
	delete htags;
}

DateTime const & Tweet::time() const
{
	return dtime;
}

string const & Tweet::text() const
{
	return post;
}

set<string> Tweet::hashTags() const
{
	return *htags;
}

bool Tweet::operator<(const Tweet& other) const
{
	if (this->time() < other.time()) return true;
	return false;
}

ostream& operator<<(ostream& os, const Tweet& t)
{
	os << t.dtime << " " << t.user()->name() << " " << t.post;
	return os;
}

User* Tweet::user() const
{
	return tuser;
}