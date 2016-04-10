#include "AVLTree.h"
#include <iostream>
#include <algorithm>
#include <string>	

const size_t AVLTree::DEFAULT_CAPACITY = 50;
const std::string AVLTree::LEFT = "LEFT";
const std::string AVLTree::RIGHT = "RIGHT";

AVLTree::AVLTree() : root_(INVALID_NODE), size_(0), capacity_(DEFAULT_CAPACITY) {
	tree_ = new Node[capacity_];
}

AVLTree::~AVLTree() {
	delete[] tree_;
}

bool AVLTree::insert(const int key, const int value) {

	if (duplicate(key) && size_ != 0) {
		std::cerr << "Key already in map" << std::endl;
		return false;
	}

	Node node(key, value);
	node.position_ = size_;
	++size_;

	if (size_ == capacity_) {
		resize(capacity_ * 2);
	}

	if (root_ == INVALID_NODE) {
		tree_[0] = node;
		root_ = node.position_;
		return true;
	}
	else {
		if (!insertNode(node, tree_[root_])) {
			return false;
		}

		std::cout << "Node in position: " << tree_[node.position_].position_ << std::endl;
		std::cout << "\tParent: " << tree_[node.position_].parent_ << "\n" << std::endl;
		return true;
	}
}

size_t AVLTree::getHeight() {
	if (size_ == 0) {
		return 0;
	}
	else {
		return findHeight(tree_[root_], 0);
	}
}

size_t AVLTree::findHeight(const Node& node, size_t currHeight) {
	if (node.leftChild_ == INVALID_NODE && node.rightChild_ == INVALID_NODE) {
		return ++currHeight;
	}
	else if (node.leftChild_ == INVALID_NODE) {
		return findHeight(tree_[node.rightChild_], ++currHeight);
	}
	else if (node.rightChild_ == INVALID_NODE) {
		return findHeight(tree_[node.leftChild_], ++currHeight);
	}
	else {
		return std::max(findHeight(tree_[node.leftChild_], ++currHeight), 
			findHeight(tree_[node.rightChild_], ++currHeight));
	}
}

size_t AVLTree::getSize() {
	return size_;
}

void AVLTree::print() {
	print(root_, 0);
}

void AVLTree::print(const size_t node, size_t numTabs) {
	if (node == INVALID_NODE) {
		return;
	}
	
	print(tree_[node].rightChild_, ++numTabs);

	for (size_t i = 0; i < numTabs; ++i) {
		std::cout << "\t";
	}

	std::cout << tree_[node].data_.key_ << ", " << tree_[node].data_.value_ << std::endl;
	print(tree_[node].leftChild_, ++numTabs);
}

bool AVLTree::find(const int key, int& value) {
	if (!find(tree_[root_], key, value)) {
		std::cerr << "Unable to find " << key << " in the map!" << std::endl;
		return false;
	}
	return true;
}

bool AVLTree::find(Node& currNode, const int key, int& value) {
	if (currNode.data_.key_ == key) {
		value = currNode.data_.value_;
		return true;
	}
	else if (key > currNode.data_.key_ && currNode.rightChild_ != INVALID_NODE) {
		find(tree_[currNode.rightChild_], key, value);
	}
	else if (key < currNode.data_.key_ && currNode.leftChild_ != INVALID_NODE) {
		find(tree_[currNode.leftChild_], key, value);
	}
	else {
		return false;
	}
}

std::vector<int> AVLTree::findRange(const int lowkey, const int highkey) {
	std::vector<int> keys;
	for (size_t i = 0; i < size_; ++i) {
		if (tree_[i].data_.key_ >= lowkey && tree_[i].data_.key_ <= highkey) {
			keys.push_back(tree_[i].data_.key_);
			keys.push_back(tree_[i].data_.value_);
		}
	}
	return keys;
}

bool AVLTree::insertNode(Node& node, Node& currNode) {
	if (currNode.data_.key_ == node.data_.key_) {
		return false;
	}
	else if (currNode.data_.key_ > node.data_.key_) {
		if (currNode.leftChild_ == INVALID_NODE) {
			add(node, currNode, LEFT);
			return true;
		}
		else {
			return insertNode(node, tree_[currNode.leftChild_]);
		}
	}
	else if (currNode.data_.key_ < node.data_.key_) {
		if(currNode.rightChild_ == INVALID_NODE) {
			add(node, currNode, RIGHT);
			return true;
		}
		else {
			return insertNode(node, tree_[currNode.rightChild_]);
		}
	}
	return false;
}

void AVLTree::add(Node& newNode, Node& parent, const std::string& whichChild) {
	tree_[newNode.position_] = newNode;
	if (whichChild == RIGHT) {
		parent.rightChild_ = newNode.position_;
	}
	else if (whichChild == LEFT) {
		parent.leftChild_ = newNode.position_;
	}
	else {
		std::cerr << "Luke, I am not your father" << std::endl;
	}
	tree_[newNode.position_].parent_ = parent.position_;
}

void AVLTree::resize(const size_t newCapacity) {
	capacity_ = newCapacity;					// Set capacity to the new capacity
	Node* newTree_ = new Node[capacity_];		// Create new tree with given capacity

	// Copy over elements
	for (size_t i = 0; i < size_; ++i) {
		newTree_[i] = tree_[i];
	}

	delete[] tree_;					// Delete old tree
	this->tree_ = newTree_;			// Set new tree to our tree
}

bool AVLTree::duplicate(const int key) {
	for (size_t i = 0; i < size_; ++i) {
		if (tree_[i].data_.key_ == key) {
			return true;
		}
	}
	return false;
}
