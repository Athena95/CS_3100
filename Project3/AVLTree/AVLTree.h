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

	bool find(const int key, const int value);
	std::vector<int> findRange(const int lowkey, const int highkey);

private:
	std::vector<Node> tree_;
	size_t height_, root_;

	bool insertNode(Node& node, Node& currNode);
	void print(const size_t node, const size_t numTabs);
	bool find(Node& currNode, const int key, const int value);
};
