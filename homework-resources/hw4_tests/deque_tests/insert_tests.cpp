//
// Insertion tests for UnrolledLinkedList
//

#include "list_utils.h"

#include <random_generator.h>


// add one item and check that it's there
TEST(DequeInsertBack, OneItemAdd)
{
	DequeStr list;

	list.push_back("a");

	EXPECT_EQ("a", list.operator[](0));
	EXPECT_EQ(false, list.empty());
}

TEST(DequeInsertFront, OneItemAdd)
{
	DequeStr list;

	list.push_front("a");

	EXPECT_EQ("a", list.operator[](0));
	EXPECT_EQ(false, list.empty());
}


TEST(DequeInsert, EmptyString)
{
	DequeStr list;

	list.push_back("");

	EXPECT_EQ(1, list.size());
	EXPECT_EQ("", list.operator[](0));
}

// add three items and check that they're there
TEST(DequeInsertBack, ThreeItemAdd)
{
	// first we create a vector to hold our data
	std::vector<std::string> contents{"768", "1024", "1536"};

	// then we create a new list with that data
	DequeStr * populatedList = makeList(contents);

	// then we assert that the list contains that data
	EXPECT_TRUE(checkListContent(populatedList, contents));

	delete populatedList;
}

// add three items and check that they're there
TEST(DequeInsertFront, ThreeItemAdd)
{
	// first we create a vector to hold our data
	std::vector<std::string> contents{"768", "1024", "1536"};

	// then we create a new list with that data
	DequeStr * populatedList = makeList(contents, false);

	// then we assert that the list contains that data
	EXPECT_TRUE(checkListContent(populatedList, contents));

	delete populatedList;
}

TEST(DequeInsert, FrontThenBack)
{
	DequeStr list;

	list.push_front("fred");
	list.push_back("bob");

	EXPECT_TRUE(checkListContent(&list, {"fred", "bob"}));
}

TEST(DequeInsert, BackThenFront)
{
	DequeStr list;

	list.push_back("bob");
	list.push_front("fred");

	EXPECT_TRUE(checkListContent(&list, {"fred", "bob"}));
}

#define ARRSIZE 10

TEST(DequeInsertBack, ARRSIZEPlusOne)
{
	std::vector<std::string> contents = makeRandomAlphaStringVector(ARRSIZE + 1, 574, 16, false);

	DequeStr * populatedList = makeList(contents);

	EXPECT_TRUE(checkListContent(populatedList, contents));

	delete populatedList;
}


TEST(DequeInsertFront, ARRSIZEPlusOne)
{
	std::vector<std::string> contents = makeRandomAlphaStringVector(ARRSIZE + 1, 37, 16, false);

	DequeStr * populatedList = makeList(contents, false);

	EXPECT_TRUE(checkListContent(populatedList, contents));

	delete populatedList;
}

TEST(DequeInsertBack, 50RandomElements)
{
	const size_t numElements = 50;
	const size_t numTrials = 30;
	const RandomSeed origSeed = 70;
	const size_t stringLength = 8;

	// generate list of random seeds and iterate through them
	for (RandomSeed seed : makeRandomSeedVector(numTrials, origSeed))
	{
		std::vector<std::string> contents(makeRandomAlphaStringVector(numElements, seed, stringLength, true));

		DequeStr *list = makeList(contents);

		EXPECT_TRUE(checkListContent(list, contents));

		delete list;
	}

}

TEST(DequeInsertFront, 50RandomElements)
{
	const size_t numElements = 50;
	const size_t numTrials = 30;
	const RandomSeed origSeed = 689;
	const size_t stringLength = 8;

	// generate list of random seeds and iterate through them
	for (RandomSeed seed : makeRandomSeedVector(numTrials, origSeed))
	{
		std::vector<std::string> contents(makeRandomAlphaStringVector(numElements, seed, stringLength, true));

		DequeStr *list = makeList(contents, false);

		EXPECT_TRUE(checkListContent(list, contents));

		delete list;
	}

}

TEST(DequeInsertBack, 5x1000RandomElements)
{
	const size_t numElements = 1000;
	const size_t numTrials = 30;
	const RandomSeed origSeed = 463948;
	const size_t stringLength = 10;

	// generate list of random seeds and iterate through them
	for (RandomSeed seed : makeRandomSeedVector(numTrials, origSeed))
	{
		std::vector<std::string> contents(makeRandomAlphaStringVector(numElements, seed, stringLength, true));

		DequeStr *list = makeList(contents);

		EXPECT_TRUE(checkListContent(list, contents));

		delete list;
	}

}

TEST(DequeInsertFront, 5x1000RandomElements)
{
	const size_t numElements = 1000;
	const size_t numTrials = 30;
	const RandomSeed origSeed = 232;
	const size_t stringLength = 10;

	// generate list of random seeds and iterate through them
	for (RandomSeed seed : makeRandomSeedVector(numTrials, origSeed))
	{
		std::vector<std::string> contents(makeRandomAlphaStringVector(numElements, seed, stringLength, true));

		DequeStr *list = makeList(contents, false);

		EXPECT_TRUE(checkListContent(list, contents));

		delete list;
	}

}
