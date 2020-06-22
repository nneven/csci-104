#include "twiteng.h"
#include <string>
using namespace std;

TwitEng::TwitEng()
{
	users = new map<string, User*>;
	hashtags = new map<string, set<Tweet*> >;
}

TwitEng::~TwitEng()
{
	
	for (map<string, User*>::iterator it = users->begin(); it != users->end(); ++it)
	{
		delete it->second;
	}
	delete users;
	delete hashtags;
}

bool TwitEng::parse(char* filename)
{
	int count;
	string line, name, following;
	ifstream ifile(filename);
	ifile >> count;
	if (ifile.fail()) return true;
	getline(ifile, line);
	if  (count < 1) return true;
	// Parse users and followers
	for (int i = 0; i < count; i++)
	{
		getline(ifile, line);
		stringstream ss(line);
		ss >> name;
		if (users->find(name) == users->end())
		{
			User* u = new User(name);
			users->insert(make_pair(name, u));
		}
		while (ss >> following) {
		
			if (users->find(following) == users->end())
			{
				User* u = new User(following);
				users->insert(make_pair(following, u));
			}
			users->find(name)->second->addFollowing(users->find(following)->second);
			users->find(following)->second->addFollower(users->find(name)->second);
		}
	}

	// Parse tweets
	// getline(ifile, line); EDIT
	while (getline(ifile, line))
	{
		// DateTime
		if ((int)line.size() < 19);
		string name, date = line.substr(0, 19);
		line.erase(0, 19);

		DateTime dt = DateTime(stoi(date.substr(11, 13)), stoi(date.substr(14, 16)), stoi(date.substr(17, 19)), stoi(date.substr(0, 4)), stoi(date.substr(5, 7)), stoi(date.substr(8, 10)));

		// Name and text
		stringstream ss(line);
		ss >> name;
		User* u = users->find(name)->second;
		string text = ss.str();
		text.erase(0, name.size() + 2);
		Tweet* t = new Tweet(u, dt, text);
		u->addTweet(t);
	}

	// Create hashtag map
	for (map<string, User*>::iterator it = users->begin(); it != users->end(); ++it)
	{
		list<Tweet*> posts = it->second->tweets();
		for (list<Tweet*>::iterator it2 = posts.begin(); it2 != posts.end(); ++it2)
		{
			set<string> htags = (*it2)->hashTags();
			for (set<string>::iterator it3 = htags.begin(); it3 !=  htags.end(); ++it3)
			{
				string ht = *it3;
				convLower(ht);
				if (hashtags->find(ht) == hashtags->end())
				{
					set<Tweet*> t;
					hashtags->insert(make_pair(ht, t));
				}
				hashtags->find(ht)->second.insert(*it2);
			}
		}
	}

	return false;

}

void TwitEng::addTweet(const string& username, const DateTime& time, const string& text)
{
	if (users->find(username) == users->end())
	{
		User* u = new User(username);
		users->insert(make_pair(username, u));
	}
	User* u = users->find(username)->second;
	Tweet* tw = new Tweet(u, time, text);
	u->addTweet(tw);
	set<string> ht = tw->hashTags();
	for (set<string>::iterator it = ht.begin(); it != ht.end(); ++it)
	{
		string word = *it;
		convLower(word);
		if (hashtags->find(word) == hashtags->end())
		{
			set<Tweet*> t;
			hashtags->insert(make_pair(word, t));
		}
		hashtags->find(word)->second.insert(tw);
	}
}

vector<Tweet*> TwitEng::search(vector<string>& terms, int strategy)
{	
	vector<Tweet*> result;
	if (terms.empty()) return result;
	if (strategy) // AND
	{
		set<Tweet*> t;
		for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it)
		{
			if (hashtags->find(*it) != hashtags->end())
			{
				set<Tweet*> tweets = hashtags->find(*it)->second;
				for (set<Tweet*>::iterator it2 = tweets.begin(); it2 != tweets.end(); ++it2)
				{
					t.insert(*it2);
				}
			}
		}
		if (!t.empty()) result.insert(result.begin(), t.begin(), t.end());	
	} else { // OR
		if (hashtags->find(terms.front()) != hashtags->end())
		{
			set<Tweet*> tweets = hashtags->find(terms.front())->second;
			for (set<Tweet*>::iterator it = tweets.begin(); it != tweets.end(); ++it)
			{
				bool add = true;
				set<string> ht = (*it)->hashTags();
				for (int i = 0; i < (int)terms.size(); i++)
				{
					if (ht.find(terms[i]) == ht.end()) add = false;
				}
				if (add) result.push_back(*it);
			}
		}
	}

	return result;
}

void TwitEng::dumpFeeds()
{
	for (map<string, User*>::iterator it = users->begin(); it != users->end(); ++it)
	{
		ofstream ofile(it->first + ".feed");
		ofile << it->first << endl;
		vector<Tweet*> feed = it->second->getFeed();

		for(vector<Tweet*>::iterator it2 = feed.begin(); it2 != feed.end(); ++it2)
		{
			ofile << **it2 << endl;
			cout << **it2 << endl;
		}
	}
}