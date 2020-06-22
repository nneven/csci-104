#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
	// Constructor/destructor
	AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
	virtual ~AVLNode();

	// Getter/setter for the node's height.
	char getBalance () const;
	void setBalance (char balance);
	void updateBalance(char diff);

	// Getters for parent, left, and right. These need to be redefined since they
	// return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
	// for more information.
	virtual AVLNode<Key, Value>* getParent() const override;
	virtual AVLNode<Key, Value>* getLeft() const override;
	virtual AVLNode<Key, Value>* getRight() const override;

protected:
	char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
	Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
	return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
	balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
	balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
	return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
	return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
	return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
	virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
	virtual void remove(const Key& key);  // TODO
protected:
	virtual void nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

	// Add helper functions here
	bool isLeftChild(AVLNode<Key, Value>* child, AVLNode<Key, Value>* parent);
	bool isRightChild(AVLNode<Key, Value>* child, AVLNode<Key, Value>* parent);
	virtual void insertHelper(const std::pair<const Key, Value> &new_item, AVLNode<Key, Value>* node);
	void insertFix(AVLNode<Key, Value>* node, AVLNode<Key, Value>* parent);
	void rotateLeft(AVLNode<Key, Value>* node);
	void rotateRight(AVLNode<Key, Value>* node);

};

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
	// TODO
	insertHelper(new_item, static_cast<AVLNode<Key, Value>*>(this->root_));
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertHelper(const std::pair<const Key, Value> &item, AVLNode<Key, Value>* node)
{	
	// INSERT
	if (node == NULL)
	{
		this->root_ = new AVLNode<Key, Value>(item.first, item.second, NULL);
		return;
	}
	else if (item.first == node->getKey()) node->setValue(item.second);
	else if (item.first < node->getKey()) {
		if (node->getLeft() == NULL)
		{
			node->setLeft(new AVLNode<Key, Value>(item.first, item.second, node));
			if (abs(node->getBalance()) == 1) node->setBalance(0);
			else
			{
				//int balance = BinarySearchTree<Key, Value>::height(node->getRight()) - BinarySearchTree<Key, Value>::height(node->getLeft());
				node->setBalance(-1);
				insertFix(node->getLeft(), node);
			}
		} 
		else insertHelper(item, node->getLeft());
	} else if (item.first > node->getKey()) {
		if (node->getRight() == NULL)
		{
			node->setRight(new AVLNode<Key, Value>(item.first, item.second, node));
			if (abs(node->getBalance()) == 1) node->setBalance(0);
			else
			{
				// int balance = BinarySearchTree<Key, Value>::height(node->getRight()) - BinarySearchTree<Key, Value>::height(node->getLeft());
				node->setBalance(1); 
				insertFix(node->getRight(), node);
			}
		}
		else insertHelper(item, node->getRight());
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* node, AVLNode<Key, Value>* parent)
{
	if (parent == NULL || parent->getParent() == NULL) return;
	AVLNode<Key, Value> * gParent = parent->getParent();
	if (isLeftChild(parent, gParent)) gParent->updateBalance(-1);
	if (isRightChild(parent, gParent)) gParent->updateBalance(1);

	// std::cout << (int)gParent->getBalance() << " " << (int)parent->getBalance() << std::endl;

	// CASE 1 (return)
	if (abs(gParent->getBalance()) == 0) return;

	// CASE 2 (recurse)
	else if (abs(gParent->getBalance()) == 1) insertFix(parent, gParent);

	// CASE 3 (zigzag)
	else if (abs(gParent->getBalance()) == 2)
	{
		// LEFT LEFT
		if (gParent->getBalance() == -2 && parent->getBalance() == -1)
		{
			rotateRight(gParent);
			parent->setBalance(0);
			gParent->setBalance(0);
		}

		// RIGHT RIGHT
		else if (gParent->getBalance() == 2 && parent->getBalance() == 1)
		{
			rotateLeft(gParent);
			parent->setBalance(0);
			gParent->setBalance(0);
		}

		// LEFT RIGHT
		else if (gParent->getBalance() == -2 && parent->getBalance() == 1)
		{
			rotateLeft(parent);
			rotateRight(gParent);

			if (node->getBalance() == -1)
			{
				parent->setBalance(0);
				gParent->setBalance(1);
				node->setBalance(0);
			}
			else if (node->getBalance() == 0)
			{
				parent->setBalance(0);
				gParent->setBalance(0);
				node->setBalance(0);
			}
			else if (node->getBalance() == 1)
			{
				parent->setBalance(-1);
				gParent->setBalance(0);
				node->setBalance(0);
			}
		}

		// RIGHT LEFT
		else if (gParent->getBalance() == 2 && parent->getBalance() == -1)
		{
			rotateRight(parent);
			rotateLeft(gParent);

			if (node->getBalance() == 1)
			{
				parent->setBalance(0);
				gParent->setBalance(-1);
				node->setBalance(0);
			}
			else if (node->getBalance() == 0)
			{
				parent->setBalance(0);
				gParent->setBalance(0);
				node->setBalance(0);
			}
			else if (node->getBalance() == -1)
			{
				parent->setBalance(1);
				gParent->setBalance(0);
				node->setBalance(0);
			}
		}
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{

}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* node)
{
	AVLNode<Key, Value> * parent = node->getParent();
	AVLNode<Key, Value> * child = node->getRight();
	AVLNode<Key, Value> * subtree = child->getLeft();

	if (subtree) subtree->setParent(node);
	node->setRight(subtree);
	child->setLeft(node);
	child->setParent(parent);
	node->setParent(child);
	if (parent == NULL) 
	{
		this->root_ = child;
		this->root_->setParent(NULL);
	}
	else if (parent != NULL && isLeftChild(node, parent)) parent->setLeft(child);
	else if (parent != NULL && isRightChild(node, parent)) parent->setRight(child);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* node)
{
	AVLNode<Key, Value> * parent = node->getParent();
	AVLNode<Key, Value> * child = node->getLeft();
	AVLNode<Key, Value> * subtree = child->getRight();

	if (subtree) subtree->setParent(node);
	node->setLeft(subtree);
	child->setRight(node);
	child->setParent(parent);
	node->setParent(child);
	if (parent == NULL) this->root_ = child;
	else if (parent != NULL && isLeftChild(node, parent)) parent->setLeft(child);
	else if (parent != NULL && isRightChild(node, parent)) parent->setRight(child);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
	BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
	char tempB = n1->getBalance();
	n1->setBalance(n2->getBalance());
	n2->setBalance(tempB);
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isLeftChild(AVLNode<Key, Value>* child, AVLNode<Key, Value>* parent)
{
	return child == parent->getLeft();
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isRightChild(AVLNode<Key, Value>* child, AVLNode<Key, Value>* parent)
{
	return child == parent->getRight();
}

#endif
