#include "twiteng.h"
using namespace std;

TwitEng::TwitEng()
{

}

TwitEng::~TwitEng()
{
	for (vector<Tweet*>::iterator it = tweets.begin(); it != tweets.end(); ++it)
	{
		delete *it;
	}
	for (map<string, User*>::iterator it = users.begin(); it != users.end(); ++it)
	{
		delete it->second;
	}
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
		if (users.find(name) == users.end())
		{
			User* u = new User(name);
			users.insert(make_pair(name, u));
		}
		while (ss >> following) {
		
			if (users.find(following) == users.end())
			{
				User* u = new User(following);
				users.insert(make_pair(following, u));
			}
			users.find(name)->second->addFollowing(users.find(following)->second);
			users.find(following)->second->addFollower(users.find(name)->second);
		}
	}

	// Parse tweets
	while (getline(ifile, line))
	{

		if (line == "") break;
		// DateTime
		string word, name, date = line.substr(0, 19);
		line.erase(0, 19);

		DateTime dt = DateTime(stoi(date.substr(11, 13)), stoi(date.substr(14, 16)), stoi(date.substr(17, 19)), stoi(date.substr(0, 4)), stoi(date.substr(5, 7)), stoi(date.substr(8, 10)));

		// Name and text
		stringstream ss(line);
		ss >> name;
		User* u = users.find(name)->second;
		string text = ss.str();
		text.erase(0, name.size() + 2);
		Tweet* t = new Tweet(u, dt, text);
		tweets.push_back(t);
		u->addFeed(t);
		ss >> word;
		if (word[0] == '@')
		{
			word = word.substr(1);
			users[word]->addMention(t);
		} else {
			u->addTweet(t);
			while (ss >> word)
			{
				if (word[0] == '@')
				{
					word = word.substr(1);
					users[word]->addMention(t);
				}
			}
		}
	}

	// Create hashtag map
	for (map<string, User*>::iterator it = users.begin(); it != users.end(); ++it)
	{
		list<Tweet*> posts = it->second->tweets();
		for (list<Tweet*>::iterator it2 = posts.begin(); it2 != posts.end(); ++it2)
		{
			set<string> htags = (*it2)->hashTags();
			for (set<string>::iterator it3 = htags.begin(); it3 !=  htags.end(); ++it3)
			{
				string ht = *it3;
				convLower(ht);
				if (hashtags.find(ht) == hashtags.end())
				{
					set<Tweet*> t;
					hashtags.insert(make_pair(ht, t));
				}
				hashtags.find(ht)->second.insert(*it2);
			}
		}
	}

	return false;

}

void TwitEng::addTweet(const string& username, const DateTime& time, const string& text)
{
	if (users.find(username) == users.end())
	{
		User* u = new User(username);
		users.insert(make_pair(username, u));
	}
	User* u = users.find(username)->second;
	Tweet* tw = new Tweet(u, time, text);
	u->addTweet(tw);
	set<string> ht = tw->hashTags();
	for (set<string>::iterator it = ht.begin(); it != ht.end(); ++it)
	{
		string word = *it;
		convLower(word);
		if (hashtags.find(word) == hashtags.end())
		{
			set<Tweet*> t;
			hashtags.insert(make_pair(word, t));
		}
		hashtags.find(word)->second.insert(tw);
	}
}

void TwitEng::addFollow(const std::string& username, const std::string& following)
{
	if (users.find(username) == users.end() || users.find(following) == users.end()) cout << "ERROR: user(s) do no exist";

	User* u = users[username];
	User* f = users[following];
	u->addFollowing(f);
	f->addFollower(u);
}

vector<Tweet*> TwitEng::search(vector<string>& terms, int strategy)
{	
	vector<Tweet*> result;
	if (terms.empty()) cout << "ERROR: no hashtags"; return result;
	if (strategy) // AND
	{
		set<Tweet*> t;
		for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it)
		{
			if (hashtags.find(*it) != hashtags.end())
			{
				set<Tweet*> tweets = hashtags.find(*it)->second;
				for (set<Tweet*>::iterator it2 = tweets.begin(); it2 != tweets.end(); ++it2)
				{
					t.insert(*it2);
				}
			}
		}
		result.insert(result.begin(), t.begin(), t.end());	
	} else { // OR
		if (hashtags.find(terms.front()) != hashtags.end())
		{
			set<Tweet*> tweets = hashtags.find(terms.front())->second;
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
	hsort(result, TweetComp());
	return result;
}

void TwitEng::dumpFeeds()
{
	for (map<string, User*>::iterator it = users.begin(); it != users.end(); ++it)
	{
		ofstream ofile(it->first + ".feed");
		ofile << it->first << endl;
		vector<Tweet*> feed = it->second->getFeed();
		hsort(feed, TweetComp());
		for(vector<Tweet*>::iterator it2 = feed.begin(); it2 != feed.end(); ++it2)
		{
			ofile << **it2 << endl;
		}
	}
}

void TwitEng::dumpMentions()
{
	for (map<string, User*>::iterator it = users.begin(); it != users.end(); ++it)
	{
		ofstream ofile(it->first + ".mentions");
		ofile << it->first << endl;
		vector<Tweet*> mentions = it->second->getMentions();
		hsort(mentions, TweetComp());
		for (vector<Tweet*>::iterator it2 = mentions.begin(); it2 != mentions.end(); ++it2)
		{
			ofile << **it2 << endl;
		}
	}
}

void TwitEng::saveData(const std::string& filename)
{
	if (filename.empty()) cout << "ERROR: no filename given";
	ofstream ofile(filename);
	ofile << users.size() << endl;
	set<Tweet*> allTweets;
	for (map<string, User*>::iterator it = users.begin(); it != users.end(); ++it)
	{
		ofile << it->first;
		set<User*> following = it->second->following();
		list<Tweet*> tweets = it->second->tweets();
		allTweets.insert(tweets.begin(), tweets.end());
		for (set<User*>::iterator it2 = following.begin(); it2 != following.end(); ++it2)
		{
			ofile << " " << (*it2)->name();
		}
		ofile << endl;
	}
	for (set<Tweet*>::iterator it = allTweets.begin(); it != allTweets.end(); ++it)
	{
		ofile << **it << endl;
	}
}

void TwitEng::strongConnect(int index, User* u, stack<User*>& s, int& count, ofstream& ofile)
{
	u->setIndex(index);
	u->setLowlink(index);
	index = index + 1;
	u->onStack(true);
	s.push(u);

	set<User*> following = u->following();
	for (set<User*>::iterator it = following.begin(); it != following.end(); ++it)
	{
		if ((*it)->getIndex() == -1)
		{
			strongConnect(index, *it, s, count, ofile);
			u->setLowlink(min(u->getLowlink(), (*it)->getLowlink()));
		} else if ((*it)->onStack()) {
			u->setLowlink(min(u->getLowlink(), (*it)->getIndex()));
		}
	}

	if (u->getLowlink() == u->getIndex())
	{
		ofile << "Component " << count << endl;
		User* w;
		do {
			w = s.top();
			s.pop();
			w->onStack(false);
			ofile << w->name() << endl;
		} while (w->name() != u->name());
		ofile << endl;
		++count;
	}
}

void TwitEng::tarjan(const std::string& filename)
{
	ofstream ofile(filename);
	int count = 1;
	int index = 0;
	stack<User*> s;
	for (map<string, User*>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (it->second->getIndex() == -1) strongConnect(index, it->second, s, count, ofile);
	}
}