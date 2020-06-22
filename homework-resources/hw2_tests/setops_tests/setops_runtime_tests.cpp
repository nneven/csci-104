//
// CS104 SetOps runtime tests
//



#include <gtest/gtest.h>

#include <functional>
#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <runtime_evaluator.h>
#include <random_generator.h>
#include <set>

#include "setops.h"

void masterSet(std::set<std::string>& s, int numElements);
void fillSet(std::set<std::string>& s, int numElements);

// Global decl
std::set<std::string> master;

void masterSet(std::set<std::string>& s, int numElements)
{
  for(int i=0; i < numElements; i++){
    std::stringstream ss;
    ss << i;
    s.insert(ss.str());
  }
}
void fillSet(std::set<std::string>& s, int numElements)
{
  if((size_t)numElements > master.size())
    {
      throw std::invalid_argument("numElements too big");
    }
  std::set<std::string>::iterator it = master.begin();
  for(int i=0; i < numElements; i++){
    s.insert(*it);
    it++;
  }
}

TEST(SetOpsRuntime, Intersection)
{
   masterSet(master, 1<<18);
	RuntimeEvaluator evaluator("Intersection", 10, 16, 5, [&](uint64_t numElements, RandomSeed seed)
	{
	  std::set<std::string> s1, s2; 
	  for(uint64_t i = 0; i < numElements; i++) { fillSet(s1, numElements); fillSet(s2, numElements); }
	  
	  BenchmarkTimer timer;
	  std::set<std::string> s3 = s1 & s2; 
	  timer.stop();
	  
	  return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEARITHMIC));
}

TEST(SetOpsRuntime, Union)
{
   masterSet(master, 1<<18);
  RuntimeEvaluator evaluator("Union", 10, 16, 5, [&](uint64_t numElements, RandomSeed seed)
	{
	  std::set<std::string> s1, s2; 
	  for(uint64_t i = 0; i < numElements; i++) { fillSet(s1, numElements); fillSet(s2, numElements); }
	  
	  BenchmarkTimer timer;
	  std::set<std::string> s3 = s1 | s2; 
	  timer.stop();
	  
	  return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEARITHMIC));
}

TEST(SetOpsRuntime, Difference)
{
   masterSet(master, 1<<18);
  RuntimeEvaluator evaluator("Difference", 10, 16, 5, [&](uint64_t numElements, RandomSeed seed)
	{
	  std::set<std::string> s1, s2; 
	  for(uint64_t i = 0; i < numElements; i++) {fillSet(s1, numElements); fillSet(s2, numElements);}
	  
	  BenchmarkTimer timer;
	  std::set<std::string> s3 = s1 - s2; 
	  timer.stop();
	  
	  return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEARITHMIC));
}
