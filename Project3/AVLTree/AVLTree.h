#pragma once
#include "Node.h"
#include <vector>
#include <limits>

// Class creates an AVL Tree
class AVLTree {
public:

	// Constructor
	AVLTree();

	// Destructor
	~AVLTree();

	/*
	 * Inserts a key-value pair into the AVL tree
	 * @param key- key for the pair
	 * @param value- value for the pair
	 * returns a boolean representing the success of the insert
	 * O(n)
	 */
	bool insert(const int key, const int value);

	/*
	 * Returns the height of the tree
	 * See findHeight() function for specific details
	 */
	size_t getHeight();

	/*
	 * Returns the size of the tree
	 * O(1)
	 */
	size_t getSize();

	/*
	 * Calls recursive print
	 * see private print() for more details
	 */
	void print();

	/*
	 * Finds the pair with key = key, and places it's value in value
	 * @param key- key to search for
	 * @param value- value to find a value for
	 * returns a boolean based on the success of the search
	 * O(log(n))
	 */
	bool find(const int key, int& value);

	/*
	 * Finds all key-value pairs within the specified range
	 * @param lowkey- low range of keys to find
	 * @param highkey- high range of keys to find
	 * returns a vector containing the keys between lowkey -> highkey
	 * O(n)
	 */
	std::vector<int> findRange(const int lowkey, const int highkey);

private:

	// Private variables
	Node* tree_;
	size_t root_, size_, capacity_;

	// Private static variables
	static const size_t DEFAULT_CAPACITY;
	static const std::string LEFT, RIGHT;

	/*
	 * Adds a node to the tree
	 * @param newNode- new node to add
	 * @param parent- parent of new node to add
	 * @param whichChild- either RIGHT or LEFT
	 * O(1)
	 */
	void add(Node& newNode, Node& parent, const std::string& whichChild);

	/*
	 * Finds a home for the node to insert
	 * @param node- node to find a home for
	 * @param currNode- current node we're interviewing for foster parent responsibilities
	 */
	bool insertNode(Node& node, Node& currNode);

	/*
	 * Prints the subtree recursively
	 * @param node- starting node to print
	 * @param numTabs- number of tabs to print to reach specified indenting
	 * O(n)
	 */
	void print(const size_t node, const size_t numTabs);

	/*
	 * Recursive helper function for public find
	 */
	bool find(Node& currNode, const int key, int& value);

	/*
	 * Finds the height of any subtree
	 * @param node- current node to work with
	 * @param currHeight- current height
	 * returns the max height of the subtree
	 * O(n)
	 */
	size_t findHeight(const Node& node, size_t currHeight);

	/*
	 * Resizes the array
	 * @param newCapacity- new capacity for the array
	 * O(n)
	 */
	void resize(const size_t newCapacity);

	/*
	 * Determines if a key is already in the tree
	 * @param key- key to find in the tree
	 * returns true if key is already in tree, false if not
	 * O(n)
	 */
	bool duplicate(const int key);

};
