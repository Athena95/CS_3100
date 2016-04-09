#pragma once
#include "Node.h"
#include <vector>
#include <limits>

class AVLTree {
public:

	AVLTree();
	bool insert(const int key, const int value);
	size_t getHeight();
	size_t getSize();
	void print();

	bool find(const int key, int& value);
	std::vector<int> findRange(const int lowkey, const int highkey);

private:
	Node* tree_;
	size_t root_, size_, capacity_;

	static const size_t DEFAULT_CAPACITY;
	static const std::string LEFT, RIGHT;

	bool insertNode(Node& node, Node& currNode);
	void print(const size_t node, const size_t numTabs);
	bool find(Node& currNode, const int key, int& value);
	size_t findHeight(const Node& node, size_t currHeight);
	void resize(const size_t newCapacity);
};
