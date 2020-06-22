//
// CS104 Heap test suite
//

// comment in to enable special checks that verify that your keyToLocation and store correlate properly
//#define CHECK_MAP_CORRELATION

#ifdef CHECK_MAP_CORRELATION
// if needed, make sure we can acces the private variables needed for correlation checking
#define private public
#define protected public
#endif

#include <heap.h>

#ifdef CHECK_MAP_CORRELATION
#undef private
#undef protected
#endif


#include <gtest/gtest.h>

#include <random_generator.h>

#include <sstream>
#include <tuple>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>

#define RANDOM_HEAP_ARY 0
const int MAX_HEAP_ARY = 26;
const int DEFAULT_HEAP_ARY = 2;

// Declaration for the type of item that will be stored in the heap.
typedef int IntType;

// Declaration for the type of std::heap used when checking during stress tests.
typedef std::priority_queue<IntType, std::deque<IntType>, std::greater<IntType> > __CPP_PRIORITY_QUEUE_TYPE_DECL;


// The random seed used to initialize the random number generator. If set to std::random_device()() then the
// tests will truly be random. Otherwise it should be set to some literal integer.
#define RANDOM_SEED 57821

// Testing setup.
class HeapTest : public testing::Test
{
protected:
	HeapTest()
	{
#if RANDOM_HEAP_ARY
		__RANDOM_NUMBER_GENERATOR randomGenerator{ RANDOM_SEED };
			D_ARY = randomGenerator() % MAX_HEAP_ARY + 3;
#else
		D_ARY = DEFAULT_HEAP_ARY;
#endif
	}
	~HeapTest() { }
	virtual void SetUp() { }
	virtual void TearDown() { }

	int D_ARY;
};

typedef Heap<int> HEAP_T;

// typename T,
//          typename TComparator = std::equal_to<T>,
//          typename PComparator = std::less<double>,
//          typename Hasher = std::hash<T> >
// class Heap


#ifdef CHECK_MAP_CORRELATION

template<typename T>
testing::AssertionResult checkMapCorrelation(Heap<T> & heap)
{
	for(size_t index = 0; index < heap.store_.size(); ++index)
	{
		std::pair<double, T> const & item = heap.store_[index];

		typename decltype(Heap<T>::keyToLocation_)::iterator indexIter = heap.keyToLocation_.find(item.second);

		if(indexIter == heap.keyToLocation_.end())
		{
			return testing::AssertionFailure() << "Map correlation error!  In store_, key " << item.second << " (priority " << item.first << ") is at index " << index << ", but it is missing from keyToLocation_!";
		}
		else if(indexIter->second != index)
		{
			return testing::AssertionFailure() << "Map correlation error!  In store_, key " << item.second << " (priority " << item.first << ") is at index " << index << ", but in keyToLocation_, it's at index " << indexIter->second;
		}
	}

	return testing::AssertionSuccess();
}

#else

// dummy function -- does nothing
template<typename T>
testing::AssertionResult checkMapCorrelation(Heap<T> & heap)
{
	return testing::AssertionSuccess();
}

#endif

/**
 * Check that the given heap contains the elements from contents.
 * Will remove all elements from the heap.
 * Assumes that each integer has been inserted into the heap with priority the same as the integer.
 * @param heap
 * @param contents
 * @return
 */
testing::AssertionResult checkHeapContents(Heap<int> & heap, std::vector<int> contents, bool doSort=true)
{
	// sort vector least to greatest so that the order of elements matches the order in the heap
        if(doSort) std::sort(contents.begin(), contents.end());

	for(size_t index = 0; index < contents.size(); ++index)
	{
		if(heap.empty())
		{
			return testing::AssertionFailure() << "Heap is missing " << (contents.size() - index) << " elements!  Only has " << index << ", should have had " << contents.size();
		}

		if(heap.top() != contents[index])
		{
			return testing::AssertionFailure() << "Incorrect element value at depth " << index << "!  Was " << heap.top() << ", expected " << contents[index];
		}

		heap.pop();
	}

	if(!heap.empty())
	{
		return testing::AssertionFailure() << "Heap has extra elements!  Should have had " << contents.size() << "elements";
	}

	return testing::AssertionSuccess();
}

TEST_F(HeapTest, ConstructionDestruction)
{
	Heap<IntType> heap(D_ARY);
}

TEST_F(HeapTest, InitiallyEmpty)
{
	Heap<IntType> heap(D_ARY);
	EXPECT_TRUE(heap.empty());
}


TEST_F(HeapTest, SingleItemPush)
{
	Heap<IntType> heap(D_ARY);
	heap.push(1);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(1, heap.top());
}

TEST_F(HeapTest, SingleItemPushPop)
{
	Heap<IntType> heap(D_ARY);
	heap.push(1);
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_TRUE(heap.empty());
}

TEST_F(HeapTest, TwoElementPush_LowPriFirst)
{
	Heap<IntType> heap(D_ARY);
	heap.push(3);
	heap.push(10);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(3, heap.top());

	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
}

TEST_F(HeapTest, TwoElementPush_HighPriFirst)
{
	Heap<IntType> heap(D_ARY);
	heap.push(50);
	heap.push(49);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(49, heap.top());

	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(50, heap.top());
}

TEST_F(HeapTest, TwoElementsSamePriority)
{
	Heap<IntType> heap(D_ARY);
	heap.push(50);
	heap.push(50);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_TRUE((heap.top() == 50) || (heap.top() == 20));
}

TEST_F(HeapTest, ThreeElementPush_10_20_30)
{
	Heap<IntType> heap(D_ARY);
	heap.push(10);
	heap.push(20);
	heap.push(30);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());
}

TEST_F(HeapTest, ThreeElementPush_10_30_20)
{
	Heap<IntType> heap(D_ARY);
	heap.push(10);
	heap.push(30);
	heap.push(20);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());
}

TEST_F(HeapTest, ThreeElementPush_20_10_30)
{
	Heap<IntType> heap(D_ARY);
	heap.push(20);
	heap.push(10);
	heap.push(30);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());
}

TEST_F(HeapTest, ThreeElementPush_20_30_10)
{
	Heap<IntType> heap(D_ARY);
	heap.push(20);
	heap.push(30);
	heap.push(10);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());
}

TEST_F(HeapTest, ThreeElementPush_30_10_20)
{
	Heap<IntType> heap(D_ARY);
	heap.push(30);
	heap.push(10);
	heap.push(20);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());
}

TEST_F(HeapTest, ThreeElementPush_30_20_10)
{
	Heap<IntType> heap(D_ARY);
	heap.push(30);
	heap.push(20);
	heap.push(10);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());
}

TEST_F(HeapTest, ThreeElementPush_String)
{
        Heap<std::string> heap(D_ARY);
	heap.push("C");
	heap.push("B");
	heap.push("A");

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ("A", heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ("B", heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ("C", heap.top());
}


TEST_F(HeapTest, ThreeElementPush_TrinaryHeap)
{
	Heap<IntType> heap(3);
	heap.push(30);
	heap.push(20);
	heap.push(10);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());
}

TEST_F(HeapTest, ThreeElementPush_QuaternaryHeap)
{
	Heap<IntType> heap(4);
	heap.push(30);
	heap.push(20);
	heap.push(10);
	heap.push(5);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(5, heap.top());

	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());

	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());

	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());
}

TEST_F(HeapTest, ThreeElementDecrease_RootOnly)
{
	Heap<IntType> heap(D_ARY);
	heap.push(40);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(40, heap.top());
	heap.decreaseKey(40, 20);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());
}
TEST_F(HeapTest, ThreeElementDecrease_Root1Node)
{
	Heap<IntType> heap(D_ARY);
	heap.push(40);
	heap.push(30);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());

	heap.decreaseKey(30, 15);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(15, heap.top());
}
TEST_F(HeapTest, ThreeElementDecrease_Child)
{
	Heap<IntType> heap(D_ARY);
	heap.push(40);
	heap.push(30);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());

	heap.decreaseKey(40, 15);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(15, heap.top());
}
TEST_F(HeapTest, ThreeElementDecrease_Zero_Level_4Node)
{
	Heap<IntType> heap(D_ARY);
	heap.push(40);
	heap.push(30);
	heap.push(20);
	heap.push(10);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.decreaseKey(40, 35);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(35, heap.top());
}
TEST_F(HeapTest, ThreeElementDecrease_Zero_Level_5Node)
{
	Heap<IntType> heap(D_ARY);
	heap.push(50);
	heap.push(40);
	heap.push(30);
	heap.push(20);
	heap.push(10);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.decreaseKey(50, 45);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(40, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(45, heap.top());
}
TEST_F(HeapTest, ThreeElementDecrease_One_Level_4Node)
{
	Heap<IntType> heap(D_ARY);
	heap.push(40);
	heap.push(30);
	heap.push(20);
	heap.push(10);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.decreaseKey(40, 15);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(15, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());
}
TEST_F(HeapTest, ThreeElementDecrease_One_Level_5Node)
{
	Heap<IntType> heap(D_ARY);
	heap.push(50);
	heap.push(40);
	heap.push(30);
	heap.push(20);
	heap.push(10);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.decreaseKey(50, 15);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(15, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(40, heap.top());
}
TEST_F(HeapTest, ThreeElementDecrease_Two_Levels_4Node)
{
	Heap<IntType> heap(D_ARY);
	heap.push(40);
	heap.push(30);
	heap.push(20);
	heap.push(10);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.decreaseKey(40, 5);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(5, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());
	heap.pop();

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());
}
TEST_F(HeapTest, ThreeElementDecrease_Two_Levels_5Node)
{
	Heap<IntType> heap(D_ARY);
	heap.push(50);
	heap.push(40);
	heap.push(30);
	heap.push(20);
	heap.push(10);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());

	heap.decreaseKey(50, 5);

	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(5, heap.top());

	heap.pop();
	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(10, heap.top());

	heap.pop();
	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(20, heap.top());

	heap.pop();
	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(30, heap.top());

	heap.pop();
	EXPECT_TRUE(checkMapCorrelation(heap));
	EXPECT_EQ(40, heap.top());
}

TEST(HeapStress, 50x50RandomElements_BinaryHeap)
{
	const RandomSeed masterSeed = 3764;
	const size_t numTrials = 50;
	const size_t numElements = 50;
	const size_t d = 2;
	const size_t pushNumerator = 7;
	const size_t pushDenominator = 8;
	std::vector<RandomSeed> seedVector = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed trialSeed : seedVector)
	{
		std::vector<int> data = makeRandomNumberVector<int>(numElements, 0, numElements * 10, trialSeed, true);
		Heap<int> heap(d);
		std::set<int> keys;

		for(int value : data)
		{
		  // push each value with itself as the priority so that sorting the vector will match the internal sort of the heap
		  if(value%pushDenominator < pushNumerator) { // push a fraction of the time
		    if(keys.find(value) == keys.end()){
		      heap.push( value);
		      keys.insert(value);
		    }
		  }
		  else { // pop the top element
		    if(!heap.empty()){
			keys.erase(heap.top());
			heap.pop();
		      }
		  }
		}
		std::vector<int> actualData(keys.begin(), keys.end());

		EXPECT_TRUE(checkMapCorrelation(heap));
		EXPECT_TRUE(checkHeapContents(heap, actualData));
	}
}

TEST(HeapStress, 50x50RandomElements_QuaternaryHeap)
{
	const RandomSeed masterSeed = 99;
	const size_t numTrials = 50;
	const size_t numElements = 50;
	const size_t d = 4;
	const size_t pushNumerator = 7;
	const size_t pushDenominator = 8;

	std::vector<RandomSeed> seedVector = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed trialSeed : seedVector)
	{
		std::vector<int> data = makeRandomNumberVector<int>(numElements, 0, numElements * 10, trialSeed, true);
		Heap<int> heap(d);
		std::set<int> keys;

		for(int value : data)
		{
			// push each value with itself as the priority so that sorting the vector will match the internal sort of the heap
			if(value%pushDenominator < pushNumerator) { // push a fraction of the time
				if(keys.find(value) == keys.end()){
				  heap.push(  value);
				  keys.insert(value);
				}
			}
			else { // pop the top element
				if(!heap.empty()){
					keys.erase(heap.top());
					heap.pop();
				}
			}
		}

		std::vector<int> actualData(keys.begin(), keys.end());

		EXPECT_TRUE(checkMapCorrelation(heap));
		EXPECT_TRUE(checkHeapContents(heap, actualData));
	}
}

TEST(HeapStress, 10x50RandomElements_QuaternaryDecrease)
{
	const RandomSeed masterSeed = 20043;
	const size_t numTrials = 10;
	const size_t numElements = 50;
	const size_t d = 4;
	const size_t pushNumerator = 5;
	const size_t decreaseNumerator = 2;
	const size_t Denominator = 8;

	std::vector<RandomSeed> seedVector = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed trialSeed : seedVector)
	{
		std::vector<int> data = makeRandomNumberVector<int>(numElements, 1, numElements * 10, trialSeed, true);
		Heap<int> heap(d);
		//std::map<int,double> keys;
		std::set<int> priorities; // to avoid priority ties
		std::vector<std::tuple<std::string,int, int> > ops;
		for(int value : data)
		{
			// push each value with itself as the priority so that sorting the vector will match the internal sort of the heap
			if (value % Denominator < pushNumerator)
			{ // push a fraction of the time
				if (priorities.find(value) == priorities.end())
				{
					//std::cout << "Pushing " << value << " with priority " << value << std::endl;
				  ops.push_back(std::make_tuple("push", value, value));
					heap.push(value);
					priorities.insert(value);

					EXPECT_TRUE(checkMapCorrelation(heap));
				}
			}
			else if ((value % Denominator) >= pushNumerator &&
			         (value % Denominator) < (pushNumerator + decreaseNumerator))
			{
				if (!priorities.empty())
				{
					// Choose a random element in the map
					int chosen = static_cast<int>(value % priorities.size());
					int pri = -1;
					for (const int& p : priorities)
					{
						if (chosen == 0)
						{
  						        pri = p;
							break;
						}
						else
						{
							chosen--;
						}
					}
					int myRand = makeRandomNumber<int>(0, value - 1, static_cast<RandomSeed>(value));
					double decreased = pri - (myRand % pri);
					if (priorities.find(decreased) == priorities.end())
					{ // if priority is unique
  					        heap.decreaseKey(pri, decreased);
						priorities.erase(pri);
						priorities.insert(decreased);
						//std::cout << "Decreased from priority " << pri << " to " << decreased << std::endl;
						ops.push_back(std::make_tuple("decrease", pri, decreased));

						EXPECT_TRUE(checkMapCorrelation(heap));
					}
				}
			}
			else
			{ // pop the top element
				if (!heap.empty())
				{
					//std::cout << "Popping element " << heap.top() << std::endl;
					ops.push_back(std::make_tuple("popped", heap.top(),  -1));
					priorities.erase(heap.top());
					heap.pop();

					EXPECT_TRUE(checkMapCorrelation(heap));
				}
			}
		}
		std::vector<int > tempData(priorities.begin(), priorities.end());
		std::sort(tempData.begin(), tempData.end(), [](const int &a,
		                                               const int &b) -> bool
			  { return a < b; });

		std::vector<int> actualData = tempData;
		// for (const int &p : tempData)
		// {
		// 	actualData.push_back(p);
		// }

		std::stringstream ss1;
		ss1 << std::endl;
		for (auto t : ops)
		{
			ss1 << std::get<0>(t) << " : key=" << std::get<1>(t);
			if (std::get<0>(t) != "popped")
			{
				ss1 << " pri=" << std::get<2>(t);
			}
			ss1 << std::endl;
		}
		EXPECT_TRUE(checkHeapContents(heap, actualData, false)) << ss1.str();
	}
}


TEST(HeapStress, 2x10000RandomElements_Binary)
{
	const RandomSeed masterSeed = 2434;
	const size_t numTrials = 2;
	const size_t numElements = 10000;
	const size_t d = 2;
	const size_t pushNumerator = 7;
	const size_t pushDenominator = 8;

	std::vector<RandomSeed> seedVector = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed trialSeed : seedVector)
	{
		std::vector<int> data = makeRandomNumberVector<int>(numElements, 0, numElements * 10, trialSeed, true);
		Heap<int> heap(d);
		std::set<int> keys;

		for(int value : data)
		{
			// push each value with itself as the priority so that sorting the vector will match the internal sort of the heap
		  if(value%pushDenominator < pushNumerator) { // push a fraction of the time
		    if(keys.find(value) == keys.end()){
		      heap.push( value);
		      keys.insert(value);
		    }
		  }
		  else { // pop the top element
		    if(!heap.empty()){
			keys.erase(heap.top());
			heap.pop();
		      }
		  }
		}
		std::vector<int> actualData(keys.begin(), keys.end());

		EXPECT_TRUE(checkMapCorrelation(heap));
		EXPECT_TRUE(checkHeapContents(heap, actualData));
	}
}
