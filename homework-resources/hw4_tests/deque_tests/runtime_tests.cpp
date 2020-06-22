//
// Runtime tests for UnrolledLinkedList
//

#include "list_utils.h"

#include <runtime_evaluator.h>

#include <gtest/gtest.h>

TEST(DequeRuntime, Get)
{
	RuntimeEvaluator runtimeEvaluator("DequeStr::get()", 0, 19, 30, [&](uint64_t numElements, RandomSeed)
	{
		DequeStr list;

		// fill the list from 0 to n elements
		for(uint64_t element = 0; element < numElements; ++element)
		{
			list.push_back("a");
		}

		// get the value in the middle of the list in case they've implemented backwards traversal
		// (like I did when I did this assignment)
		BenchmarkTimer timer;
		list.operator[](numElements / 2);
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEAR));
}

TEST(DequeRuntime, PushBack)
{
	RuntimeEvaluator runtimeEvaluator("DequeStr::push_back()", 0, 20, 30, [&](uint64_t numElements, RandomSeed)
	{
		DequeStr list;

		// fill the list from 0 to n-1 elements
		for(uint64_t element = 0; element < numElements - 1; ++element)
		{
			list.push_back("a");
		}

		BenchmarkTimer timer;
		list.push_back("b");
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}

TEST(DequeRuntime, PushFront)
{
	RuntimeEvaluator runtimeEvaluator("DequeStr::push_front()", 0, 20, 30, [&](uint64_t numElements, RandomSeed)
	{
		DequeStr list;

		// fill the list from 0 to n-1 elements
		for(uint64_t element = 0; element < numElements - 1; ++element)
		{
			list.push_back("a");
		}

		BenchmarkTimer timer;
		list.push_front("b");
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}

TEST(DequeRuntime, PopFront)
{
	RuntimeEvaluator runtimeEvaluator("DequeStr::pop_front()", 0, 20, 30, [&](uint64_t numElements, RandomSeed)
	{
		DequeStr list;

		// fill the list from 0 to n elements
		for(uint64_t element = 0; element < numElements; ++element)
		{
			list.push_back("a");
		}

		BenchmarkTimer timer;
		list.pop_front();
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}

TEST(DequeRuntime, PopBack)
{
	RuntimeEvaluator runtimeEvaluator("DequeStr::pop_back()", 0, 20, 30, [&](uint64_t numElements, RandomSeed)
	{
		DequeStr list;

		// fill the list from 0 to n elements
		for(uint64_t element = 0; element < numElements; ++element)
		{
			list.push_back("a");
		}

		BenchmarkTimer timer;
		list.pop_back();
		timer.stop();

		return timer.getTime();
	});

	//runtimeEvaluator.enableDebugging();
	runtimeEvaluator.setCorrelationThreshold(1);
	runtimeEvaluator.evaluate();

	EXPECT_TRUE(runtimeEvaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}


