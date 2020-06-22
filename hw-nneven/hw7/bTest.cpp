#include <iostream>
#include "bst.h"

using namespace std;

int main() {

	/*
	BinarySearchTree<std::string, std::string> testTree;
	testTree.remove("supercalifragilisticexpialodocious");
	//testTree.print();

	testTree.clear();
	testTree.insert(std::make_pair("blah", "blah"));
	testTree.insert(std::make_pair("bluh", "blug"));
	testTree.remove("supercalifragilisticexpialodocious");

	cout << "REMOVE 1" << endl;
	BinarySearchTree<int, double> bst;
	bst.insert(std::make_pair(1, 1.0));
	bst.print();
	bst.remove(1);
	bst.clear();
	bst.print();

	cout << "REMOVE 1" << endl;
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(3, 1.0));
	bst.print();
	bst.remove(1);
	bst.print();
	bst.clear();

	cout << "REMOVE 3" << endl;
	bst.insert(std::make_pair(3, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.print();
	bst.remove(3);
	bst.print();
	bst.clear();


	cout << "REMOVE 2" << endl;
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(1, 1.0));
	bst.insert(std::make_pair(3, 1.0));
	bst.print();
	bst.remove(2);
	bst.print();
	bst.clear();

	cout << "REMOVE 5" << endl;
	bst.insert(std::make_pair(5, 1.0));
	bst.insert(std::make_pair(2, 1.0));
	bst.insert(std::make_pair(6, 1.0));
	bst.insert(std::make_pair(4, 1.0));
	bst.print();
	bst.remove(5);
	bst.print();
	bst.clear(); */

	// STRESS REMOVE
	BinarySearchTree<int, std::string> b, c, d;
	std::pair<int, std::string> item5(5, "five");
	std::pair<int, std::string> item3(3, "three");
	std::pair<int, std::string> item7(7, "seven");
	std::pair<int, std::string> item4(4, "four");
	std::pair<int, std::string> item6(6, "six");
	std::pair<int, std::string> item9(9, "nine");
	std::pair<int, std::string> item10(10, "ten");
	std::pair<int, std::string> item2(2, "two");
	std::pair<int, std::string> item8(8, "eight");
	std::pair<int, std::string> item13(13, "thirteen");
	std::pair<int, std::string> item11(11, "eleven");
	std::pair<int, std::string> item12(12, "twelve");
	std::pair<int, std::string> item15(15, "fifteen");
	std::pair<int, std::string> item14(14, "fourteen");
	std::pair<int, std::string> item16(16, "sixteen");
	std::pair<int, std::string> item17(17, "seventeen");


	b.insert(item5);
	// ASSERT_TRUE(verifyBST(b, {item5.first}));

	b.remove(7);
	// ASSERT_TRUE(verifyBST(b, {item5.first}));

	b.remove(5);
	// ASSERT_TRUE(verifyBST(b, {}));

	b.insert(item5);
	b.insert(item3);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first}));

	b.remove(5);
	// ASSERT_TRUE(verifyBST(b, {item3.first}));

	b.remove(3);
	// ASSERT_TRUE(verifyBST(b, {}));


	b.insert(item5);
	b.insert(item3);
	b.insert(item7);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first}));

	b.remove(5);
	// ASSERT_TRUE(verifyBST(b, {item3.first, item7.first}));

	b.remove(7);
	// ASSERT_TRUE(verifyBST(b, {item3.first}));

	b.remove(3);
	// ASSERT_TRUE(verifyBST(b, {}));

	b.insert(item5);
	b.insert(item3);
	b.insert(item7);
	b.insert(item4);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first}));

	b.remove(5);
	// ASSERT_TRUE(verifyBST(b, {item3.first, item7.first, item4.first}));

	b.clear();
	// ASSERT_TRUE(verifyBST(b, {}));

	b.insert(item5);
	b.insert(item3);
	b.insert(item7);
	b.insert(item4);
	b.insert(item6);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first}));

	b.remove(6);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first}));

	b.remove(4);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first}));

	b.clear();
	// ASSERT_TRUE(verifyBST(b, {}));

	b.insert(item5);
	b.insert(item3);
	b.insert(item7);
	b.insert(item4);
	b.insert(item6);
	b.insert(item9);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first, item9.first}));

	b.remove(5);
	// ASSERT_TRUE(verifyBST(b, {item3.first, item7.first, item4.first, item6.first, item9.first}));

	b.remove(7);
	// ASSERT_TRUE(verifyBST(b, {item3.first, item4.first, item6.first, item9.first}));

	b.remove(6);
	// ASSERT_TRUE(verifyBST(b, {item3.first, item4.first, item9.first}));

	b.clear();
	// ASSERT_TRUE(verifyBST(b, {}));

	b.insert(item5);
	b.insert(item3);
	b.insert(item7);
	b.insert(item4);
	b.insert(item6);
	b.insert(item9);
	b.insert(item10);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first, item9.first, item10.first}));
	
	b.print(); // FULL TREE

	b.remove(5);
	// ASSERT_TRUE(verifyBST(b, {item3.first, item7.first, item4.first, item6.first, item9.first, item10.first}));

	b.remove(9);
	// ASSERT_TRUE(verifyBST(b, {item3.first, item7.first, item4.first, item6.first, item10.first}));

	b.remove(3);
	// ASSERT_TRUE(verifyBST(b, {item7.first, item4.first, item6.first, item10.first}));

	b.remove(7);
	// ASSERT_TRUE(verifyBST(b, {item4.first, item6.first, item10.first}));

	b.remove(4);
	// ASSERT_TRUE(verifyBST(b, {item6.first, item10.first}));

	b.remove(10);
	// ASSERT_TRUE(verifyBST(b, {item6.first}));

	b.remove(10);
	// ASSERT_TRUE(verifyBST(b, {item6.first}));

	b.remove(6);
	// ASSERT_TRUE(verifyBST(b, {}));
	
	b.print(); // EMPTY TREE
	
	b.insert(item5);
	b.insert(item3);
	b.insert(item7);
	b.insert(item4);
	b.insert(item6);
	b.insert(item9);
	b.insert(item10);
	b.insert(item2);
	b.insert(item8);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first, item9.first, item10.first, item2.first, item8.first}));

	b.insert(item13);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first, item9.first, item10.first, item2.first, item8.first, item13.first}));

	b.insert(item12);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first, item9.first, item10.first, item2.first, item8.first, item13.first, item12.first}));

	b.insert(item11);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first, item9.first, item10.first, item2.first, item8.first, item13.first, item12.first, item11.first}));

	b.print(); // FULL TREE

	b.remove(13);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first, item9.first, item10.first, item2.first, item8.first, item12.first, item11.first}));

	b.remove(12);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item7.first, item4.first, item6.first, item9.first, item10.first, item2.first, item8.first, item11.first}));

	b.remove(10);
	b.remove(13);
	b.remove(7);
	b.remove(8);
	b.remove(7);
	// ASSERT_TRUE(verifyBST(b, {item5.first, item3.first, item4.first, item6.first, item9.first, item2.first, item11.first}));

	cout << "REMOVE 7 8 10 12 13" << endl;
	b.print();

	
	d.insert(item10);
	d.insert(item3);
	d.insert(item2);
	d.insert(item15);
	d.insert(item12);
	d.insert(item11);
	d.insert(item14);
	d.insert(item13);
	d.insert(item16);
	d.insert(item17);

	d.print(); // FULL TREE

	// ASSERT_TRUE(verifyBST(d, {item10.first, item3.first, item2.first, item15.first, item12.first, item11.first, item14.first, item13.first, item16.first, item17.first}));

	d.remove(15);

	// ASSERT_TRUE(verifyBST(d, {item10.first, item3.first, item2.first, item12.first, item11.first, item14.first, item13.first, item16.first, item17.first}));

	d.remove(10);
	// ASSERT_TRUE(verifyBST(d, {item3.first, item2.first, item12.first, item11.first, item14.first, item13.first, item16.first, item17.first}));

	cout << "REMOVE 10 15" << endl;
	d.print();

	c.insert(item5);
	c.insert(item3);
	c.insert(item7);
	c.insert(item4);
	c.insert(item6);
	c.insert(item9);
	c.insert(item10);
	c.insert(item2);
	c.insert(item8);
	c.insert(item15);
	c.insert(item11);
	c.insert(item14);
	c.insert(item13);
	c.insert(item12);

	// c.print(); // FULL TREE

	// ASSERT_TRUE(verifyBST(c, {item5.first, item3.first, item7.first, item4.first, item6.first, item9.first, item10.first, item2.first, item8.first, item15.first, item11.first, item14.first, item13.first, item12.first}));
	c.remove(15);

	c.remove(14);
	// ASSERT_TRUE(verifyBST(c, {item5.first, item3.first, item7.first, item4.first, item6.first, item9.first, item10.first, item2.first, item8.first, item11.first, item13.first, item12.first}));
	
	// cout << "REMOVE 14 15" << endl;
	// c.print();
}
