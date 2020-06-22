//
// CS104 Stack test cases
//

#include <stack.h>

#include <random_generator.h>

#include <gtest/gtest.h>

typedef Stack<std::string> StackString;

TEST(Stack, Empty)
{
	StackString stack;

	ASSERT_EQ(true, stack.empty());
	ASSERT_EQ(0, stack.size());
}

/*
 * The top of empty stack should throw an exception
 */
TEST(Stack, TopEmpty)
{
	StackString stack;

	EXPECT_ANY_THROW(stack.top());
}


/*
 * If we push one element, the stack should function properly
 */
TEST(Stack, OneElementPush)
{
	StackString stack;

	stack.push("Aaron");
	ASSERT_EQ(false, stack.empty());
	ASSERT_EQ(1, stack.size());
	EXPECT_EQ("Aaron", stack.top());
}

/*
 * If we push multiple elements, the stack should function properly
 */
TEST(Stack, FiveElementPush)
{
	StackString stack;

	for (int i = 0; i < 5; i++)
	{
		stack.push(std::to_string(i));
		ASSERT_EQ(false, stack.empty());
		ASSERT_EQ(i+1, stack.size());
		EXPECT_EQ(std::to_string(i), stack.top());
	}
}

TEST(Stack, OneElementPop)
{
	StackString stack;

	stack.push("Aaron");

	stack.pop();
	ASSERT_EQ(true, stack.empty());
	ASSERT_EQ(0, stack.size());
}

TEST(Stack, FiveElementPop)
{
	StackString stack;

	for (int i = 0; i < 5; i++) {
		stack.push(std::to_string(i));
	}

	for (int i = 4; i >= 0; i--)
	{
		ASSERT_EQ(i + 1, stack.size());
		EXPECT_EQ(std::to_string(i), stack.top());
		stack.pop();
	}

	ASSERT_EQ(true, stack.empty());
}

TEST(Stack, PopEmpty)
{
	StackString stack;

	EXPECT_THROW(stack.pop(), std::underflow_error);
	ASSERT_EQ(true, stack.empty());
	ASSERT_EQ(0, stack.size());
}

TEST(Stack, EmptyThenRefill)
{
	StackString stack;

	stack.push("foo");
	stack.push("bar");

	EXPECT_EQ("bar", stack.top());

	stack.pop();

	EXPECT_EQ("foo", stack.top());

	stack.pop();

	stack.push("baz");

	EXPECT_EQ("baz", stack.top());
	EXPECT_EQ(1, stack.size());
}

TEST(Stack, PopThenAdd)
{
	StackString stack;

	EXPECT_THROW(stack.pop(), std::underflow_error);


	for (int i = 0; i < 5; i++)
	{
		stack.push(std::to_string(i));
		ASSERT_EQ(i+1, stack.size());
		EXPECT_EQ(std::to_string(i), stack.top());
	}

	for (int i = 4; i >= 0; i--)
	{
		ASSERT_EQ(i+1, stack.size());
		EXPECT_EQ(std::to_string(i), stack.top());
		stack.pop();
	}
	ASSERT_EQ(true, stack.empty());
}

TEST(StackStress, 50x50Elements)
{
	const RandomSeed masterSeed = 34379;
	const size_t numElements = 50;
	const size_t numTrials = 50;
	const size_t stringLength = 8;

	StackString stack;

	for(RandomSeed trialSeed : makeRandomSeedVector(numTrials, masterSeed))
	{
		std::vector<std::string> contents = makeRandomAlphaStringVector(numElements, trialSeed, stringLength, true);

		// put the data in
		for(auto contentsIter = contents.begin(); contentsIter != contents.end(); ++contentsIter)
		{
			stack.push(*contentsIter);
		}

		//now, read it back out in reverse
		for(auto contentsIter = contents.rbegin(); contentsIter != contents.rend(); ++contentsIter)
		{
			EXPECT_EQ(*contentsIter, stack.top());
			stack.pop();
		}

		EXPECT_TRUE(stack.empty());
	}
}

TEST(StackStress, 5x1000Elements)
{
	const RandomSeed masterSeed = 34379;
	const size_t numElements = 1000;
	const size_t numTrials = 5;
	const size_t stringLength = 8;

	StackString stack;

	for(RandomSeed trialSeed : makeRandomSeedVector(numTrials, masterSeed))
	{
		std::vector<std::string> contents = makeRandomAlphaStringVector(numElements, trialSeed, stringLength, true);

		// put the data in
		for(auto contentsIter = contents.begin(); contentsIter != contents.end(); ++contentsIter)
		{
			stack.push(*contentsIter);
		}

		//now, read it back out in reverse
		for(auto contentsIter = contents.rbegin(); contentsIter != contents.rend(); ++contentsIter)
		{
			EXPECT_EQ(*contentsIter, stack.top());
			stack.pop();
		}

		EXPECT_TRUE(stack.empty());
	}
}

TEST(StackStress, 2x10000Elements)
{
	const RandomSeed masterSeed = 34379;
	const size_t numElements = 10000;
	const size_t numTrials = 2;
	const size_t stringLength = 10;

	StackString stack;

	for(RandomSeed trialSeed : makeRandomSeedVector(numTrials, masterSeed))
	{
		std::vector<std::string> contents = makeRandomAlphaStringVector(numElements, trialSeed, stringLength, true);

		// put the data in
		for(auto contentsIter = contents.begin(); contentsIter != contents.end(); ++contentsIter)
		{
			stack.push(*contentsIter);
		}

		//now, read it back out in reverse
		for(auto contentsIter = contents.rbegin(); contentsIter != contents.rend(); ++contentsIter)
		{
			EXPECT_EQ(*contentsIter, stack.top());
			stack.pop();
		}

		EXPECT_TRUE(stack.empty());
	}
}
