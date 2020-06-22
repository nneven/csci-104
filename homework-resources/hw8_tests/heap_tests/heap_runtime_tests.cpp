//
// CS104 Heap runtime tests
//

#include <heap.h>

#include <gtest/gtest.h>

#include <functional>

#include <runtime_evaluator.h>
#include <random_generator.h>

// dimension of heap to use in these tests
#define D_ARY 2

TEST(HeapRuntime, Push)
{

	RuntimeEvaluator evaluator("Heap::push() with d=2", 2, 17, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		Heap<int> heap(D_ARY);
		std::set<int> keys;
		for(int value = 1; value < static_cast<int>(numElements); ++value) // don't add the first element, 0
		{
		  if(keys.find(value) == keys.end()){
   		     heap.push( value);
		     keys.insert(value);
		  }
		}
		std::vector<int> actualData(keys.begin(), keys.end());

		double smallerThanMin = (double)heap.top()-1;
		BenchmarkTimer timer;
		// worst case for MinHeap: add the smallest element
		heap.push(smallerThanMin);
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}

TEST(HeapRuntime, Decrease)
{

	RuntimeEvaluator evaluator("Heap::decrease() with d=2", 2, 17, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		Heap<int> heap(D_ARY);
		std::set<int> keys;
		for(int value = 1; value < static_cast<int>(numElements); ++value) // don't add the first element, 0
		{
		  if(keys.find(value) == keys.end()){
   		     heap.push( value);
		     keys.insert(value);
		  }
		}
		std::vector<int> actualData(keys.begin(), keys.end());

		double smallerThanMin = (double)actualData.front()-1;
		BenchmarkTimer timer;
		// worst case for MinHeap: decreaseKey the biggest element to become the smallest priority
		heap.decreaseKey(actualData.back(), smallerThanMin);
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}


TEST(HeapRuntime, Pop)
{

	RuntimeEvaluator evaluator("Heap::pop() with d=2", 2, 18, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		Heap<int> heap(D_ARY);
		std::set<int> keys;

		for(int value = 0; value < static_cast<int>(numElements); ++value)
		{
		  if(keys.find(value) == keys.end()){
   		     heap.push(value);
		     keys.insert(value);
		  }
		}

		BenchmarkTimer timer;
		heap.pop();
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}
