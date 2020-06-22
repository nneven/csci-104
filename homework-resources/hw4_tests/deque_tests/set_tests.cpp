//
// Tests for UnrolledLinkedList's pop operations
//

#include "list_utils.h"

#include <random_generator.h>

TEST(DequeSet, OneItem)
{
	DequeStr list;

	list.push_back("a");

	EXPECT_EQ("a", list.operator[](0));

	list.operator[](0) = "z";

	EXPECT_EQ("z", list.operator[](0));
}

std::vector<std::string> quickBrownFox = {"The", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dog", "."};

TEST(DequeSet, First)
{
	DequeStr * list = makeList(quickBrownFox);

	list->operator[](0) =  "A";
	EXPECT_EQ("A", list->operator[](0));

	delete list;
}

TEST(DequeSet, Last)
{
	DequeStr * list = makeList(quickBrownFox);

	list->operator[](9) = "!";
	EXPECT_EQ("!", list->operator[](9));

	delete list;
}

TEST(DequeSet, Middle)
{
	DequeStr * list = makeList(quickBrownFox);

	list->operator[](4) = "perambulated";
	EXPECT_EQ("perambulated", list->operator[](4));

	delete list;
}

TEST(DequeSet, 50x50RandomElements)
{
	const size_t numElements = 50;
	const size_t numTrials = 30;
	const RandomSeed origSeed = 9009;
	const size_t stringLength = 8;

	// generate list of random seeds and iterate through them
	for (RandomSeed seed : makeRandomSeedVector(numTrials, origSeed))
	{
		std::vector<std::string> contents(makeRandomAlphaStringVector(numElements, seed, stringLength, true));

		DequeStr *list = makeList(contents);

		for(size_t index = 0; index < numElements; index++)
		{
		  list->operator[](index) = std::to_string(index);
		}

		for(size_t index = 0; index < numElements; index++)
		{
			EXPECT_EQ(std::to_string(index), list->operator[](index));
		}


		delete list;
	}

}
