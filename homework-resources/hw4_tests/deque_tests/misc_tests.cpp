//
// Miscellaneous tests for UnrolledLinkedList
//

#include "list_utils.h"

TEST(Deque, ConstructionDestruction)
{
	DequeStr list;
}

TEST(Deque, NoElements)
{
	DequeStr list;

	EXPECT_TRUE(list.empty());
	EXPECT_EQ(0, list.size());
}

TEST(Deque, Front_PushBack)
{
	std::vector<std::string> content = {"sup", "er", "cal", "i", "frag", "il", "ist", "ic", "exp", "i", "alo", "doc", "ious"};

	DequeStr * list = makeList(content);

	EXPECT_EQ(list->operator[](0), "sup");

	delete list;
}

TEST(Deque, Front_PushFront)
{
	std::vector<std::string> content = {"sup", "er", "cal", "i", "frag", "il", "ist", "ic", "exp", "i", "alo", "doc", "ious"};

	DequeStr * list = makeList(content, false);

	EXPECT_EQ(list->operator[](0), "sup");

	delete list;
}

TEST(Deque, Back_PushBack)
{
	std::vector<std::string> content = {"sup", "er", "cal", "i", "frag", "il", "ist", "ic", "exp", "i", "alo", "doc", "ious"};

	DequeStr * list = makeList(content, false);

	EXPECT_EQ(list->operator[](list->size()-1), "ious");

	delete list;
}

TEST(Deque, Back_PushFront)
{
	std::vector<std::string> content = {"sup", "er", "cal", "i", "frag", "il", "ist", "ic", "exp", "i", "alo", "doc", "ious"};

	DequeStr * list = makeList(content, false);

	EXPECT_EQ(list->operator[](list->size()-1), "ious");

	delete list;
}
