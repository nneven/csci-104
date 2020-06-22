#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "user_code_runner.h"

//Aaron's password: arnspwd
//Bryan's password: bryanpwd
//Calvin's password: clvnpswd
//David's password: davidpwd
//Emanuel's password: emnlpswd

/*
UserCodeRunner::UserCodeRunner(std::string const & workingDirectory, 
							   std::string const & executablePath, 
							   std::vector<std::string> args, 
							   std::string const & outputFilePath, 
							   bool useValgrind)

UserCodeRunner::execute()

UserCodeRunner::setStdin(std::string const & stdinContents, std::string const & stdinFilePath)
*/

std::string getStringFromIStream(std::ifstream& input)
{
	std::stringstream ss; 
	ss << input.rdbuf(); 

	return ss.str(); 
}

TEST(Login, UserExistsPasswordWrong)
{
	std::string testName = "UserExistsPasswordWrong";
	std::string stdinContents = "LOGIN Aaron wrongpwd\n"
								"QUIT"; 

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	ASSERT_TRUE(consoleOutput.find("Invalid username/password") != std::string::npos) << "Console did not output "
																						 "\"Invalid username/password\""; 
}

TEST(Login, UserDoesNotExist)
{
	std::string testName = "UserDoesNotExist";
	std::string stdinContents = "LOGIN Mark UserDNE\n"
								"QUIT"; 

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	ASSERT_TRUE(consoleOutput.find("Invalid username/password") != std::string::npos) << "Console did not output "
																						 "\"Invalid username/password\"";
}

TEST(Login, UserExistsPasswordCorrectDavid)
{
	std::string testName = "UserExistsPasswordCorrectDavid";
	std::string stdinContents = "LOGIN David davidpwd\n"
								"QUIT"; 

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	ASSERT_TRUE(consoleOutput.find("Login successful") != std::string::npos) << "Console did not output "
																				"\"Login successful\"";
}

TEST(Login, UserExistsPasswordCorrectEmanuel)
{
	std::string testName = "UserExistsPasswordCorrectEmanuel";
	std::string stdinContents = "LOGIN Emanuel emnlpswd\n"
								"QUIT"; 

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	ASSERT_TRUE(consoleOutput.find("Login successful") != std::string::npos) << "Console did not output "
																				"\"Login successful\"";
}

TEST(Login, TweetCommandNoUserSignedIn)
{
	std::string testName = "TweetCommandNoUserSignedIn";
	std::string stdinContents = "TWEET This tweet should not be saved\n"
								"SAVE saves/TweetCommandNoUserSignedIn.dat\n"
								"QUIT"; 

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	ASSERT_NE(consoleOutput.find("No user logged in"), std::string::npos) << "Console did not output "
																			 "\"No user logged in\"";
}

TEST(Login, TweetCommandIncludesUser)
{
	std::string testName = "TweetCommandIncludesUser";
	std::string stdinContents = "LOGIN David davidpwd\n"
								"TWEET Emanuel This tweet should not be saved\n"
								"SAVE saves/TweetCommandIncludesUser.dat\n"
								"QUIT";

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream saveData("saves/" + testName + ".dat"); 
	ASSERT_FALSE(saveData.fail()) << "Unable to open saved data file"; 
	std::string data = getStringFromIStream(saveData); 

	ASSERT_NE(data.find("David Emanuel This tweet should not be saved"), std::string::npos) << "saved TWEET not found"; 
}

TEST(Login, TweetCommandValid)
{
	std::string testName = "TweetCommandValid";
	std::string stdinContents = "LOGIN Aaron arnspwd\n"
								"TWEET This is a valid tweet and should be saved\n"
								"SAVE saves/TweetCommandValid.dat\n"
								"QUIT"; 

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream saveData("saves/" + testName + ".dat"); 
	ASSERT_FALSE(saveData.fail()) << "Unable to open saved data file"; 
	std::string data = getStringFromIStream(saveData); 

	ASSERT_NE(data.find("Aaron This is a valid tweet and should be saved"), std::string::npos) << "saved TWEET not found";
}

TEST(Login, FollowCommandNoUserSignedIn)
{
	std::string testName = "FollowCommandNoUserSignedIn";
	std::string stdinContents = "FOLLOW Calvin\n"
								"QUIT"; 

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	ASSERT_NE(consoleOutput.find("No user logged in"), std::string::npos) << "Console did not output "
																			 "\"No user logged in\"";
}

TEST(Login, FollowCommandValid)
{
	std::string testName = "FollowCommandValid";
	std::string stdinContents = "LOGIN Aaron arnspwd\n"
								"FOLLOW Bryan\n"
								"SAVE saves/FollowCommandValid.dat\n"
								"QUIT";

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream saveData("saves/" + testName + ".dat"); 
	ASSERT_FALSE(saveData.fail()) << "Unable to open saved data file"; 
	std::string line; 

	while (std::getline(saveData, line)) 
	{
		if (line.find("Aaron") == 0 && line.find("Bryan") != std::string::npos) 
		{
			SUCCEED(); 
			return; 
		}
	}

	FAIL() << "Was not able to verify that Aaron now follows Bryan"; 
}

// LOGOUT, try and TWEET
TEST(Login, LoginLogoutTweet)
{
	std::string testName = "LoginLogoutTweet";
	std::string stdinContents = "LOGIN Aaron arnspwd\n"
								"LOGOUT\n"
								"TWEET This tweet should not show up anywhere\n"
								"SAVE saves/LoginLogoutTweet.dat\n"
								"QUIT";

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	// Check console output
	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	ASSERT_NE(consoleOutput.find("Login successful"), std::string::npos) << "Aaron not successfully logged in"; 
	ASSERT_NE(consoleOutput.find("No user logged in"), std::string::npos) << "Attempting to tweet when nobody signed in did not produce error"; 

	// Check saved data
	std::ifstream saveData("saves/" + testName + ".dat"); 
	ASSERT_FALSE(saveData.fail()) << "Unable to open saved data file";
	std::string data = getStringFromIStream(saveData); 
	ASSERT_EQ(data.find("This tweet should not show up anywhere"), std::string::npos) << "Invalid tweet saved"; 
}

TEST(Login, LoginLogoutLogin)
{
	std::string testName = "LoginLogoutLogin";
	std::string stdinContents = "LOGIN Aaron arnspwd\n"
								"LOGOUT\n"
								"LOGIN Calvin clvnpswd\n"
								"QUIT";

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	int index = consoleOutput.find("Login successful");

	ASSERT_NE(index, std::string::npos) << "Aaron was not successfully signed in"; 
	ASSERT_NE(consoleOutput.find("Login successful", index + 1), std::string::npos) << "Calvin was not successfully signed in"; 
}

// LOGOUT, try and FOLLOW
TEST(Login, LoginLogoutFollow)
{
	std::string testName = "LoginLogoutFollow";
	std::string stdinContents = "LOGIN Aaron arnspwd\n"
								"LOGOUT\n"
								"FOLLOW Calvin\n"
								"SAVE saves/LoginLogoutFollow.dat\n"
								"QUIT";

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	// Check console output
	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	ASSERT_NE(consoleOutput.find("Login successful"), std::string::npos) << "Aaron was not successfully signed in"; 
	ASSERT_NE(consoleOutput.find("No user logged in"), std::string::npos) << "Attempting to follow when nobody signed in did not cause error"; 

	
}

TEST(Login, LoginLogoutLoginTweet)
{
	std::string testName = "LoginLogoutLoginTweet";
	std::string stdinContents = "LOGIN Aaron arnspwd\n"
								"LOGOUT\n"
								"LOGIN Calvin clvnpswd\n"
								"TWEET This is a new tweet written by Calvin\n"
								"SAVE saves/LoginLogoutLoginTweet.dat\n"
								"QUIT"; 

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	int index = consoleOutput.find("Login successful");

	ASSERT_NE(index, std::string::npos) << "Aaron was not successfully signed in"; 
	ASSERT_NE(consoleOutput.find("Login successful", index + 1), std::string::npos) << "Calvin was not successfully signed in"; 

	std::ifstream saveData("saves/" + testName + ".dat"); 
	ASSERT_FALSE(saveData.fail()) << "Unable to open saved data file";
	std::string data = getStringFromIStream(saveData); 
	ASSERT_NE(data.find("Calvin This is a new tweet written by Calvin"), std::string::npos) << "Calvin's tweet was not saved";
}

TEST(Login, LoginLogoutLoginFollow)
{
	std::string testName = "LoginLogoutLoginFollow";
	std::string stdinContents = "LOGIN Bryan bryanpwd\n"
								"LOGOUT\n"
								"LOGIN Aaron arnspwd\n"
								"FOLLOW Bryan\n"
								"SAVE saves/LoginLogoutLoginFollow.dat\n"
								"QUIT";


	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	int index = consoleOutput.find("Login successful");

	ASSERT_NE(index, std::string::npos) << "Bryan was not successfully signed in"; 
	ASSERT_NE(consoleOutput.find("Login successful", index + 1), std::string::npos) << "Aaron was not successfully signed in"; 

	std::ifstream saveData("saves/" + testName + ".dat"); 
	ASSERT_FALSE(saveData.fail()) << "Unable to open saved data file";
	std::string line; 

	while (std::getline(saveData, line)) 
	{
		if (line.find("Aaron") == 0 && line.find("Bryan") != std::string::npos) 
		{
			SUCCEED(); 
			return; 
		}
	}

	FAIL() << "Aaron is not following Bryan in saved data file"; 
	
}

TEST(Login, LoginTweetLogoutLoginTweet) 
{
	std::string testName = "LoginTweetLogoutLoginTweet";
	std::string stdinContents = "LOGIN Bryan bryanpwd\n"
								"TWEET This is a new tweet written by Bryan\n"
								"LOGOUT\n"
								"LOGIN Aaron arnspwd\n"
								"TWEET This is a new tweet written by Aaron\n"
								"SAVE saves/LoginTweetLogoutLoginTweet.dat\n"
								"QUIT\n";

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	int index = consoleOutput.find("Login successful");

	ASSERT_NE(index, std::string::npos) << "Bryan was not successfully signed in"; 
	ASSERT_NE(consoleOutput.find("Login successful", index + 1), std::string::npos) << "Aaron was not successfully signed in"; 

	std::ifstream saveData("saves/" + testName + ".dat"); 
	ASSERT_FALSE(saveData.fail()) << "Unable to open saved data file";
	std::string data = getStringFromIStream(saveData); 
	ASSERT_NE(data.find("Bryan This is a new tweet written by Bryan"), std::string::npos) << "Bryan's tweet was not saved";
	ASSERT_NE(data.find("Aaron This is a new tweet written by Aaron"), std::string::npos) << "Aaron's tweet was not saved";


}

TEST(Login, LoginTweetLogoutLoginFollow)
{
	std::string testName = "LoginTweetLogoutLoginFollow";
	std::string stdinContents = "LOGIN David davidpwd\n"
								"TWEET This is a new tweet written by David\n"
								"LOGOUT\n"
								"LOGIN Calvin clvnpswd\n"
								"FOLLOW Aaron\n"
								"SAVE saves/LoginTweetLogoutLoginFollow.dat\n"
								"QUIT";

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	int index = consoleOutput.find("Login successful");

	ASSERT_NE(index, std::string::npos) << "David was not successfully signed in"; 
	ASSERT_NE(consoleOutput.find("Login successful", index + 1), std::string::npos) << "Calvin was not successfully signed in"; 

	std::ifstream saveData("saves/" + testName + ".dat"); 
	ASSERT_FALSE(saveData.fail()) << "Unable to open saved data file";
	std::string line; 

	while (std::getline(saveData, line)) 
	{
		if (line.find("Calvin") == 0 && line.find("Aaron") != std::string::npos) 
		{
			SUCCEED(); 
			return; 
		}
	}

	FAIL() << "Calvin is not following Aaron in saved data file"; 
}

TEST(Login, LoginFollowLogoutLoginTweet)
{
	std::string testName = "LoginFollowLogoutLoginTweet";
	std::string stdinContents = "LOGIN Emanuel emnlpswd\n"
								"FOLLOW Aaron\n"
								"LOGOUT\n"
								"LOGIN Aaron arnspwd\n"
								"TWEET This is a new tweet written by Aaron\n"
								"SAVE saves/LoginFollowLogoutLoginTweet.dat\n"
								"QUIT"; 

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	int index = consoleOutput.find("Login successful");

	ASSERT_NE(index, std::string::npos) << "Emanuel was not successfully signed in"; 
	ASSERT_NE(consoleOutput.find("Login successful", index + 1), std::string::npos) << "Aaron was not successfully signed in"; 

	std::ifstream saveData("saves/" + testName + ".dat"); 
	std::ifstream saveData2("saves/" + testName + ".dat"); 
	ASSERT_FALSE(saveData.fail() || saveData2.fail()) << "Unable to open saved data file";
	std::string line; 
	std::string data = getStringFromIStream(saveData); 

	ASSERT_NE(data.find("Aaron This is a new tweet written by Aaron"), std::string::npos) << "Aaron's new tweet was not saved"; 
	bool emanuelFollowsAaron = false; 

	while (std::getline(saveData2, line)) 
	{
		if (line.find("Emanuel") == 0 && line.find("Aaron") != std::string::npos) 
		{
			emanuelFollowsAaron = true;  
		}
	}

	ASSERT_TRUE(emanuelFollowsAaron) << "Emanuel is not following Aaron in saved data file"; 
}

TEST(Login, LoginFollowLogoutLoginFollow)
{
	std::string testName = "LoginFollowLogoutLoginFollow";
	std::string stdinContents = "LOGIN David davidpwd\n"
								"FOLLOW Aaron\n"
								"LOGOUT\n"
								"LOGIN Aaron arnspwd\n"
								"FOLLOW David\n"
								"SAVE saves/LoginFollowLogoutLoginFollow.dat\n"
								"QUIT";

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream stdout("stdout/" + testName + ".out"); 
	ASSERT_FALSE(stdout.fail()) << "Unable to parse console output."; 
	std::string consoleOutput = getStringFromIStream(stdout); 

	int index = consoleOutput.find("Login successful");

	ASSERT_NE(index, std::string::npos) << "David was not successfully signed in"; 
	ASSERT_NE(consoleOutput.find("Login successful", index + 1), std::string::npos) << "Aaron was not successfully signed in"; 

	std::ifstream saveData("saves/" + testName + ".dat"); 
	ASSERT_FALSE(saveData.fail()) << "Unable to open saved data file";
	std::string line; 
	
	bool davidFollowsAaron = false; 
	bool AaronFollowsDavid = false; 

	while (std::getline(saveData, line)) 
	{
		if (line.find("David") == 0 && line.find("Aaron") != std::string::npos) 
		{
			davidFollowsAaron = true;  
		}
		if (line.find("Aaron") == 0 && line.find("David") != std::string::npos) 
		{
			AaronFollowsDavid = true;
		}
	}

	ASSERT_TRUE(davidFollowsAaron && AaronFollowsDavid) << "Aaron and David are supposed to be following each other"; 

}

// Test to verify that passwords are dumped
TEST(Login, PasswordsAreSaved) 
{
	std::string testName = "LoginFollowLogoutLoginFollow";
	std::string stdinContents = "SAVE\nQUIT";

	UserCodeRunner runner(".", "../../twitter", {"twitterLarge2.dat"}, "stdout/" + testName + ".out", true); 
	runner.setStdin(stdinContents, "stdin/" + testName + ".in"); 
	runner.execute(); 

	std::ifstream saveData("saves/" + testName + ".dat"); 
	ASSERT_FALSE(saveData.fail()) << "Unable to open saved data file";
	std::string line; 
	
	bool davidPassword = false; 
	bool aaronPassword = false; 
	bool calvinPassword = false; 
	bool emanuelPassword = false; 
	bool bryanPassword = false; 

	while (std::getline(saveData, line)) 
	{
		if (line.find("David") == 0 && line.find("54062") != std::string::npos) 
		{
			davidPassword = true;  
		}
		if (line.find("Aaron") == 0 && line.find("155") != std::string::npos) 
		{
			aaronPassword = true;
		}
		if (line.find("Calvin") == 0 && line.find("61692") != std::string::npos) 
		{
			calvinPassword = true;
		}
		if (line.find("Emanuel") == 0 && line.find("31150") != std::string::npos) 
		{
			emanuelPassword = true;
		}
		if (line.find("Bryan") == 0 && line.find("34724") != std::string::npos) 
		{
			bryanPassword = true;
		}
	}

	ASSERT_TRUE(davidPassword && aaronPassword && calvinPassword && emanuelPassword && bryanPassword) << "Passwords were not saved"; 
}

