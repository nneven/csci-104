#include <iostream>
#include "avlbst.h"

using namespace std;

int main() {

// TEST(AVLBST, ConstructionDestruction)

	AVLTree<string, string> testOne;


// TEST(AVLInsert, OneNode)

	testOne.insert(make_pair("Hello World", "!!!"));
	// testOne.print();
	testOne.clear();
	// EXPECT_TRUE(verifyAVL(testTree, set<string>("Hello World")));



// TEST(AVLInsert, DoubleInsertLeft)

	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(make_pair(1, 9));
	testTree.insert(make_pair(0, 8));
	testTree.print();
	testTree.clear();

	// EXPECT_TRUE(verifyAVL(testTree, set<uint16_t>(0, 1)));


// TEST(AVLInsert, DoubleInsertRight)

	testTree.insert(make_pair(1, 9));
	testTree.insert(make_pair(2, 8));
	testTree.print();
	testTree.clear();

	// EXPECT_TRUE(verifyAVL(testTree, set<uint16_t>(1, 2)));


// TEST(AVLInsert, InsertZigZigLeft)

	cout << "ZIGZIG LEFT LEFT" << endl;
	testTree.insert(make_pair(2, 9));
	testTree.insert(make_pair(1, 8));
	testTree.insert(make_pair(0, 159));
	testTree.print();
	testTree.clear();

	// EXPECT_TRUE(verifyAVL(testTree, set<uint16_t>(0, 1, 2)));


// TEST(AVLInsert, InsertZigZigRight)

	cout << "ZIGZIG RIGHT RIGHT" << endl;
	testTree.insert(make_pair(0, 9));
	testTree.insert(make_pair(1, 8));
	testTree.insert(make_pair(2, 159));
	testTree.print();
	testTree.clear();

	// EXPECT_TRUE(verifyAVL(testTree, set<uint16_t>(0, 1, 2)));

// TEST(AVLInsert, InsertZigZagLeft)

	cout << "ZIGZAG LEFT RIGHT" << endl;
	testTree.insert(make_pair(2, 9));
	testTree.insert(make_pair(0, 8));
	testTree.insert(make_pair(1, 159));
	testTree.print();
	testTree.clear();

	// EXPECT_TRUE(verifyAVL(testTree, set<uint16_t>(0, 1, 2)));


// TEST(AVLInsert, InsertZigZagRight)

	cout << "ZIGZAG RIGHT LEFT" << endl;
	testTree.insert(make_pair(0, 9));
	testTree.insert(make_pair(2, 8));
	testTree.insert(make_pair(1, 159));
	testTree.print();
	testTree.clear();

	// EXPECT_TRUE(verifyAVL(testTree, set<uint16_t>(0, 1, 2)));

/*
// TEST(AVLInsert, 7Elements)

	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(make_pair(5, 8));
	testTree.insert(make_pair(3, 159));
	testTree.insert(make_pair(1, 9));
	testTree.insert(make_pair(10, 0x5a));
	testTree.insert(make_pair(15, 0xb));
	testTree.insert(make_pair(2, 4));
	testTree.insert(make_pair(4, 159));

	// EXPECT_TRUE(verifyAVL(testTree, set<uint16_t>(5, 3, 1, 10, 15, 2, 4)));


// TEST(AVLClear, Clear)

	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(make_pair(5, 8));
	testTree.insert(make_pair(3, 159));

	testTree.clear();

	// EXPECT_TRUE(verifyAVL(testTree, set<uint16_t>()));


// TEST(AVLInsert, Duplicates)

	AVLTree<uint16_t, uint16_t> testTree;

	testTree.insert(make_pair(5, 8));
	testTree.insert(make_pair(3, 159));
	testTree.insert(make_pair(1, 9));
	testTree.insert(make_pair(3, 0x5a));
	testTree.insert(make_pair(15, 0xb));
	testTree.insert(make_pair(1, 4));
	testTree.insert(make_pair(3, 159));

	// EXPECT_TRUE(verifyAVL(testTree, set<uint16_t>(5, 3, 1, 15)));
*/

}
