#ifndef CMDHANDLER_H
#define CMDHANDLER_H
#include "handler.h"
#include "util.h"

/**
 * Handles the QUIT command
 */
class QuitHandler : public Handler
{
public:
	QuitHandler();
	QuitHandler(Handler* next);

protected:

	virtual bool canHandle(const std::string& cmd) const;
	virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};
 
/**
 * Handles the AND command
 */
class AndHandler : public Handler
{
public:
	AndHandler();
	AndHandler(Handler* next);

protected:

	virtual bool canHandle(const std::string& cmd) const;
	virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};

/**
 * Handles the OR command
 */
class OrHandler : public Handler
{
public:
	OrHandler();
	OrHandler(Handler* next);

protected:

	virtual bool canHandle(const std::string& cmd) const;
	virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};

/**
 * Handles the TWEET command
 */
class TweetHandler : public Handler
{
public:
	TweetHandler();
	TweetHandler(Handler* next);

protected:

	virtual bool canHandle(const std::string& cmd) const;
	virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};

// Handles the FOLLOW command
class FollowHandler : public Handler
{
public:
	FollowHandler();
	FollowHandler(Handler* next);

protected:

	virtual bool canHandle(const std::string& cmd) const;
	virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};

// Handles the SAVE command
class SaveHandler : public Handler
{
public:
	SaveHandler();
	SaveHandler(Handler* next);

protected:

	virtual bool canHandle(const std::string& cmd) const;
	virtual HANDLER_STATUS_T process(TwitEng* eng, std::istream& instr) const;
};
#endif