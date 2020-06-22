all: twitter

twitter: twitter.cpp twiteng.o tweet.o user.o datetime.o util.o handler.o cmdhandler.o
	g++ -g -Wall -std=c++11 twitter.cpp twiteng.o tweet.o user.o datetime.o util.o handler.o cmdhandler.o -o twitter

twiteng.o: twiteng.h twiteng.cpp
	g++ -g -Wall -c -std=c++11 twiteng.cpp -o twiteng.o

tweet.o: tweet.h tweet.cpp
	g++ -g -Wall -c -std=c++11 tweet.cpp -o tweet.o

user.o: user.h user.cpp
	g++ -g -Wall -c -std=c++11 user.cpp -o user.o

datetime.o: datetime.h datetime.cpp
	g++ -g -Wall -c -std=c++11 datetime.cpp -o datetime.o

util.o: util.h util.cpp
	g++ -g -Wall -c -std=c++11 util.cpp -o util.o

handler.o: handler.h handler.cpp
	g++ -g -Wall -c -std=c++11 handler.cpp -o handler.o

cmdhandler.o: cmdhandler.h cmdhandler.cpp
	g++ -g -Wall -c -std=c++11 cmdhandler.cpp -o cmdhandler.o