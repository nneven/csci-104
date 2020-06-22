#include "deque.h"
#include "gtest/gtest.h"
#include <iostream>
#include <stdexcept>

TEST(DequeTest, Basic) {
	Deque<int> d;
	Deque<int> d2(10);
	EXPECT_EQ(d.empty(), true);
	EXPECT_EQ(d2.size(), 0);
	d[0] = 1;
	EXPECT_EQ(d[0], 1);
}

TEST(DequeTest, PushPopFrontBack) {
	Deque<int> d;
	Deque<int> d2(10);
	for (int i = 0; i < 10; i++)
	{
		d.push_back(i);
		d2.push_front(i);
	}
	for (int i = 0; i < 10; i++) {
		EXPECT_EQ(d[i], i);
		EXPECT_EQ(d2.size() - i - 1, d2[i]);
	}
	EXPECT_EQ(d.size(), 10);
	for (int i = 0; i < 10; i++)
	{
		d.pop_front();
		d2.pop_back();
	}
	EXPECT_EQ(d.size(), 0);
	EXPECT_EQ(d2.empty(), true);
}

TEST(DequeTest, Exceptions) {
	Deque<int> d;
	Deque<int> d2(10);
	EXPECT_THROW(d[1], std::range_error);
	EXPECT_THROW(d2[-1], std::range_error);
}