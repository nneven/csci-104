//
// CS104 Set Operations test suite
//



// make public for access to internal data


#include <gtest/gtest.h>

#include <random_generator.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>

#define private public
#define protected public

#include "setops.h"

#undef private
#undef protected



#define RANDOM_SEED 34699

//Helper function to print out a set 
std::string printSet(std::set<std::string> s3)
{
	std::string actualSet = "{"; 		//String to help print the actual resulting set

	for (std::string s : s3)
	{
		actualSet += "\"" + s + "\", "; 
	}

	actualSet = actualSet.substr(0, actualSet.size() - 2) + "}";

	return actualSet; 
}


///////////////////////////////////////
// Intersection (&) Tests Begin Here //
///////////////////////////////////////

//Intersection of two empty sets
TEST(SetOpsTestIntersection, TwoEmptySets)
{
	std::set<std::string> s1 = {};
	std::set<std::string> s2 = {};

	std::set<std::string> s3 = s1 & s2; 

	EXPECT_EQ(0, s3.size()) << "Contents differ from expected when finding the intersection of two empty sets. Expected set of size 0, but returned set of size " << s3.size() << ".";
}

//First set is empty
TEST(SetOpsTestIntersection, FirstSetEmpty) 
{
	std::set<std::string> s1 = {}; 
	std::set<std::string> s2 = {"CS104", "abc", "def"}; 

	std::set<std::string> s3 = s1 & s2; 

	EXPECT_EQ(0, s3.size()) << "Contents differ from expected when finding the intersection of one empty set followed by one non-empty set. Expected set of size 0, but returned set of size " << s3.size() << "."; 
}

//Second set is empty
TEST(SetOpsTestIntersection, SecondSetEmpty)
{
	std::set<std::string> s1 = {"CS104", "abc", "def"}; 
	std::set<std::string> s2 = {}; 

	std::set<std::string> s3 = s1 & s2; 

	EXPECT_EQ(0, s3.size()) << "Contents differ from expected when finding the intersection of one non-empty set followed by one empty set. Expected set of size 0, but returned set of size " << s3.size() << "."; 
}

//No intersection between two non-empty sets
TEST(SetOpsTestIntersection, NonIntersectingSets)
{
	std::set<std::string> s1 = {"CS104", "abc", "def"}; 
	std::set<std::string> s2 = {"EE109", "ghi", "jkl"}; 

	std::set<std::string> s3 = s1 & s2; 

	EXPECT_EQ(0, s3.size()) << "Contents differ from expected when finding the intersection of two disjoint sets. Expected set of size 0, but returned set of size " << s3.size() << "."; 
}

//Partial intersection between two non-emtpy sets
TEST(SetOpsTestIntersection, PartiallyIntersectingSets)
{
	std::set<std::string> s1 = {"different", "dffrnt", "same", "also the same"}; 
	std::set<std::string> s2 = {"also the same", "diffirent", "same", "diffferent"}; 

	std::set<std::string> s3 = s1 & s2;
	std::set<std::string> s4 = {"same", "also the same"}; 

	EXPECT_EQ(s3, s4) << "Contents differ from expected when finding the intersection of two partially-intersecting sets. Expected {\"same\", \"also the same\"}, but returned " << printSet(s3) << "."; 
}

//Two identical non-empty sets
TEST(SetOpsTestIntersection, IdenticalNonEmptySets) 
{
	std::set<std::string> s1 = {"we're all the same", "this one is the same too", "I'm the same!", "I'm also the same but all the way over here"}; 
	std::set<std::string> s2 = {"I'm also the same but all the way over here", "this one is the same too", "we're all the same", "I'm the same!"}; 

	std::set<std::string> s3 = s1 & s2;
	std::set<std::string> s4 = {"we're all the same", "this one is the same too", "I'm the same!", "I'm also the same but all the way over here"}; 

	EXPECT_EQ(s3, s4) << "Contents differ from expected when finding the intersection of two identical non-empty sets. dExpected " << printSet(s4) << ", but returned " << printSet(s3) << ".";
}

////////////////////////////////
// Union (|) Tests Begin Here //
////////////////////////////////

//Two empty sets
TEST(SetOpsTestUnion, TwoEmptySets) 
{
	std::set<std::string> s1 = {};
	std::set<std::string> s2 = {};

	std::set<std::string> s3 = s1 | s2; 

	EXPECT_EQ(0, s3.size()) << "Contents differ from expected when finding the union of two empty sets. Expected set of size 0, but returned set of size " << s3.size() << ".";
}

//First set is empty
TEST(SetOpsTestUnion, FirstSetEmpty) 
{
	std::set<std::string> s1 = {}; 
	std::set<std::string> s2 = {"CS104", "abc", "def"}; 

	std::set<std::string> s3 = s1 | s2; 

	EXPECT_EQ(s2, s3) << "Contents differ from expected when finding the union of one empty set followed by one non-empty set. Expected " << printSet(s2) << ", but returned " << printSet(s3) << "."; 
}

//Second set is empty
TEST(SetOpsTestUnion, SecondSetEmpty)
{
	std::set<std::string> s1 = {"CS104", "abc", "def"}; 
	std::set<std::string> s2 = {}; 

	std::set<std::string> s3 = s1 | s2; 

	EXPECT_EQ(s1, s3) << "Contents differ from expected when finding the union of one non-empty set followed by one empty set. Expected " << printSet(s1) << ", but returned " << printSet(s3) << "."; 
}

//Non-empty sets with no elements in common
TEST(SetOpsTestUnion, NoElementsInCommon)
{
	std::set<std::string> s1 = {"CS104", "abc", "def"}; 
	std::set<std::string> s2 = {"EE109", "ghi", "jkl"}; 

	std::set<std::string> s3 = s1 | s2; 
	std::set<std::string> s4 = {"CS104", "abc", "def", "EE109", "ghi", "jkl"}; 

	EXPECT_EQ(s4, s3) << "Contents differ from expected when finding the union of two sets with no elements in common. Expected " << printSet(s4) << ", but returned " << printSet(s3) << "."; 
}

//Non-empty sets with some overlap
TEST(SetOpsTestUnion, SomeElementsInCommon) 
{
	std::set<std::string> s1 = {"different", "dffrnt", "same", "also the same"}; 
	std::set<std::string> s2 = {"also the same", "diffirent", "same", "diffferent"}; 

	std::set<std::string> s3 = s1 | s2;
	std::set<std::string> s4 = {"different", "dffrnt", "same", "also the same", "diffirent", "diffferent"}; 

	EXPECT_EQ(s3, s4) << "Contents differ from expected when finding the union of two sets with some elements in common. Expected "<< printSet(s4) << ", but returned " << printSet(s3) << "."; 
}

//Identical non-empty sets
TEST(SetOpsTestUnion, IdenticalNonEmptySets) 
{
	std::set<std::string> s1 = {"we're all the same", "this one is the same too", "I'm the same!", "I'm also the same but all the way over here"}; 
	std::set<std::string> s2 = {"I'm also the same but all the way over here", "this one is the same too", "we're all the same", "I'm the same!"}; 

	std::set<std::string> s3 = s1 | s2;
	std::set<std::string> s4 = {"we're all the same", "this one is the same too", "I'm the same!", "I'm also the same but all the way over here"}; 

	EXPECT_EQ(s3, s4) << "Contents differ from expected when finding the union of two identical non-empty sets. Expected " << printSet(s4) << ", but returned " << printSet(s3) << ".";
}

/////////////////////////////////////
// Difference (-) Tests Begin Here //
/////////////////////////////////////

//Both empty
TEST(SetOpsTestDifference, TwoEmptySets) 
{
	std::set<std::string> s1 = {};
	std::set<std::string> s2 = {};

	std::set<std::string> s3 = s1 - s2; 

	EXPECT_EQ(0, s3.size()) << "Contents differ from expected when finding the difference of two empty sets. Expected set of size 0, but returned set of size " << s3.size() << ".";
}

//First set is empty
TEST(SetOpsTestDifference, FirstSetEmpty) 
{
	std::set<std::string> s1 = {}; 
	std::set<std::string> s2 = {"CS104", "abc", "def"}; 

	std::set<std::string> s3 = s1 - s2; 

	EXPECT_EQ(s1, s3) << "Contents differ from expected when finding the difference of one empty set and one non-empty set. Expected " << printSet(s1) << ", but returned " << printSet(s3) << "."; 
}

//Second set is empty
TEST(SetOpsTestDifference, SecondSetEmpty)
{
	std::set<std::string> s1 = {"CS104", "abc", "def"}; 
	std::set<std::string> s2 = {}; 

	std::set<std::string> s3 = s1 - s2; 

	EXPECT_EQ(s1, s3) << "Contents differ from expected when finding the difference of one non-empty set followed by one empty set. Expected " << printSet(s1) << ", but returned " << printSet(s3) << "."; 
}

//s1 == s2
TEST(SetOpsTestDifference, IdenticalNonEmptySets) 
{
	std::set<std::string> s1 = {"we're all the same", "this one is the same too", "I'm the same!", "I'm also the same but all the way over here"}; 
	std::set<std::string> s2 = {"I'm also the same but all the way over here", "this one is the same too", "we're all the same", "I'm the same!"}; 

	std::set<std::string> s3 = s1 - s2;
	std::set<std::string> s4 = {}; 

	EXPECT_EQ(s3, s4) << "Contents differ from expected when taking the difference of two identical non-empty sets. Expected " << printSet(s4) << ", but returned " << printSet(s3) << ".";
}

//s1 is a subset of s2
TEST(SetOpsTestDifference, FirstSubsetOfSecond)
{
	std::set<std::string> s1 = {"Go", "Troj"}; 
	std::set<std::string> s2 = {"Go", "U", "S", "C", "Troj", "ans!"}; 

	std::set<std::string> s3 = s1 - s2; 
	std::set<std::string> s4 = {}; 

	EXPECT_EQ(s3, s4) << "Contents differ from expected when taking the difference of two sets where the first is a subset of the second. Expected set of size 0, but returned " << printSet(s3) << "."; 
}

//s2 is a subset of s1
TEST(SetOpsTestDifference, SecondSubsetOfFirst)
{
	std::set<std::string> s2 = {"Go", "Troj"}; 
	std::set<std::string> s1 = {"Go", "U", "S", "C", "Troj", "ans!"}; 

	std::set<std::string> s3 = s1 - s2; 
	std::set<std::string> s4 = {"U", "S", "C", "ans!"}; 

	EXPECT_EQ(s3, s4) << "Contents differ from expected when taking the difference of two sets where the second is a subset of the first. Expected " << printSet(s4) << ", but returned " << printSet(s3) << "."; 
}

//s1 and s2 are disjont sets
TEST(SetOpsTestDifference, NoElementsInCommon)
{
	std::set<std::string> s1 = {"CS104", "abc", "def"}; 
	std::set<std::string> s2 = {"EE109", "ghi", "jkl"}; 

	std::set<std::string> s3 = s1 - s2; 

	EXPECT_EQ(s1, s3) << "Contents differ from expected when finding the union of two sets with no elements in common. Expected " << printSet(s1) << ", but returned " << printSet(s3) << "."; 
}