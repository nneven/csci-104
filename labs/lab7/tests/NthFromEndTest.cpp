#include "gtest/gtest.h"
#include "../LinkedList.h"
#include <stdio.h>
#include <cstdlib>
#include <vector>

TEST(NthFromEndTest, Empty) 
{
	LinkedList ll;
	EXPECT_EQ(-1, ll.NthFromEnd(0));
}

TEST(NthFromEndTest, OneNodeFunctionality)
{
	LinkedList ll;
	ll.add(1);
	EXPECT_EQ(1, ll.NthFromEnd(0));

	//edge cases
	EXPECT_EQ(-1, ll.NthFromEnd(1));
	EXPECT_EQ(-1, ll.NthFromEnd(-1));
}

TEST(NthFromEndTest, OneNodeEdgeCases)
{
	LinkedList ll;
	ll.add(1);

	//edge cases
	EXPECT_EQ(-1, ll.NthFromEnd(1));
	EXPECT_EQ(-1, ll.NthFromEnd(-1));
}

TEST(NthFromEndTest, FiveNodesFunctionality)
{
	LinkedList ll;
	ll.add(1);
	ll.add(10);
	ll.add(3);
	ll.add(7);
	ll.add(4);
	EXPECT_EQ(1, ll.NthFromEnd(0));
	EXPECT_EQ(10, ll.NthFromEnd(1));
	EXPECT_EQ(3, ll.NthFromEnd(2));
	EXPECT_EQ(7, ll.NthFromEnd(3));
	EXPECT_EQ(4, ll.NthFromEnd(4));
}

TEST(NthFromEndTest, FiveNodesEdgeCases)
{
	LinkedList ll;
	ll.add(1);
	ll.add(10);
	ll.add(3);
	ll.add(7);
	ll.add(4);

	//edge cases
	EXPECT_EQ(-1, ll.NthFromEnd(5));
	EXPECT_EQ(-1, ll.NthFromEnd(-1));
}