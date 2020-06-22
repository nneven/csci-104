#include "cmdhandler.h"
using namespace std;

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
  : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
	return cmd == "QUIT";
}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->dumpFeeds();
	eng->dumpMentions();
	return HANDLER_QUIT;
}

AndHandler::AndHandler()
{

}

AndHandler::AndHandler(Handler* next)
  : Handler(next)
{

}

bool AndHandler::canHandle(const std::string& cmd) const
{
	return cmd == "AND";
}

Handler::HANDLER_STATUS_T AndHandler::process(TwitEng* eng, std::istream& instr) const
{
	string word;
	vector<string> terms;

	while (instr >> word) terms.push_back(word);
	vector<Tweet*> result = eng->search(terms, 0);
	sort(result.begin(), result.end(), TweetComp());
	displayHits(result);
	return HANDLER_OK;
}

OrHandler::OrHandler()
{

}

OrHandler::OrHandler(Handler* next)
  : Handler(next)
{

}

bool OrHandler::canHandle(const std::string& cmd) const
{
	return cmd == "OR";
}

Handler::HANDLER_STATUS_T OrHandler::process(TwitEng* eng, std::istream& instr) const
{
	string word;
	vector<string> terms;

	while (instr >> word) terms.push_back(word);
	vector<Tweet*> result = eng->search(terms, 1);
	sort(result.begin(), result.end(), TweetComp());
	displayHits(result);
	return HANDLER_OK;
}

TweetHandler::TweetHandler()
{

}

TweetHandler::TweetHandler(Handler* next)
  : Handler(next)
{

}

bool TweetHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TWEET";
}

Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng* eng, std::istream& instr) const
{
	if (eng->getActiveUser() == NULL)
	{
		cout << "No user logged in." << endl;
		return HANDLER_ERROR;
	}

	string name, text;
	DateTime dt;
	name = eng->getActiveUser()->name();
	//instr >> name;
	getline(instr, text);
	text.erase(0, 1);
	eng->addTweet(name, dt, text);
	return HANDLER_OK;
}

FollowHandler::FollowHandler()
{

}

FollowHandler::FollowHandler(Handler* next)
  : Handler(next)
{

}

bool FollowHandler::canHandle(const std::string& cmd) const
{
	return cmd == "FOLLOW";
}

Handler::HANDLER_STATUS_T FollowHandler::process(TwitEng* eng, std::istream& instr) const
{
	if (eng->getActiveUser() == NULL)
	{
		cout << "No user logged in." << endl;
		return HANDLER_ERROR;
	}

	string user, following;
	user = eng->getActiveUser()->name();
	//instr >> user;
	instr >> following;
	eng->addFollow(user, following);
	return HANDLER_OK;
}

SaveHandler::SaveHandler()
{

}

SaveHandler::SaveHandler(Handler* next)
  : Handler(next)
{

}

bool SaveHandler::canHandle(const std::string& cmd) const
{
	return cmd == "SAVE";
}

Handler::HANDLER_STATUS_T SaveHandler::process(TwitEng* eng, std::istream& instr) const
{
	string filename;
	instr >> filename;
	eng->saveData(filename);
	return HANDLER_OK;
}

SccHandler::SccHandler()
{

}

SccHandler::SccHandler(Handler* next)
  : Handler(next)
{

}

bool SccHandler::canHandle(const std::string& cmd) const
{
	return cmd == "SCC";
}

Handler::HANDLER_STATUS_T SccHandler::process(TwitEng* eng, std::istream& instr) const
{
	string filename;
	instr >> filename;
	eng->tarjan(filename);
	return HANDLER_OK;
}

TrendingHandler::TrendingHandler()
{

}

TrendingHandler::TrendingHandler(Handler* next)
  : Handler(next)
{

}

bool TrendingHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TRENDING";
}

Handler::HANDLER_STATUS_T TrendingHandler::process(TwitEng* eng, std::istream& instr) const
{
	int n;
	instr >> n;
	if (n < 0) return HANDLER_ERROR;
	eng->trending(n);
	return HANDLER_OK;
}

LoginHandler::LoginHandler()
{

}

LoginHandler::LoginHandler(Handler* next)
  : Handler(next)
{

}

bool LoginHandler::canHandle(const std::string& cmd) const
{
	return cmd == "LOGIN";
}

Handler::HANDLER_STATUS_T LoginHandler::process(TwitEng* eng, std::istream& instr) const
{
	string name, password;
	instr >> name >> password;
	if (!(eng->login(name, password))) // failed login
	{
		cout << "Invalid usernaname/password." << endl;
		return HANDLER_ERROR;
	}

	cout << "Login successful." << endl;
	return HANDLER_OK;
}

LogoutHandler::LogoutHandler()
{

}

LogoutHandler::LogoutHandler(Handler* next)
  : Handler(next)
{

}

bool LogoutHandler::canHandle(const std::string& cmd) const
{
	return cmd == "LOGOUT";
}

Handler::HANDLER_STATUS_T LogoutHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->logout();
	return HANDLER_OK;
}
