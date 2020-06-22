//
// CS104 Heap Sort Runtime Tests
//
#include "comparators.h"

#include <hsort.h>

#include <gtest/gtest.h>

#include <functional>

#include <runtime_evaluator.h>
#include <random_generator.h>

TEST(HeapSortRuntime, Runtime)
{
	intCompareLess comparator;

	RuntimeEvaluator evaluator("hsort()", 1, 18, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		std::vector<int> data = makeRandomIntVector(numElements, seed, true);

		BenchmarkTimer timer;
		hsort(data, comparator);
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.3);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEARITHMIC));
}

