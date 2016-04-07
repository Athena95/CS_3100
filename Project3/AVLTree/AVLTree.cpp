#include "AVLTree.h"
#include <iostream>
#include <string>	

AVLTree::AVLTree() : height_(0), root_(INVALID_NODE) {}

bool AVLTree::insert(const int key, const int value) {
	Node node(key, value);
	node.position_ = tree_.size();
	tree_.push_back(node);

	if (root_ == INVALID_NODE) {
		root_ = node.position_;
		return true;
	}
	else {
		if (!insertNode(node, tree_[root_])) {
			tree_.pop_back();
			return false;
		}

		std::cout << "Node in position: " << node.position_ << std::endl;
		std::cout << "\tParent: " << node.parent_ << "\n" << std::endl;
		return true;
	}
}

size_t AVLTree::getHeight() {
	return height_;
}

size_t AVLTree::getSize() {
	return tree_.size();
}

void AVLTree::print() {
	print(root_, 0);
}

void AVLTree::print(const size_t node, size_t numTabs) {
	if (node == INVALID_NODE) {
		return;
	}
	
	print(tree_[node].rightChild_, ++numTabs);

	for (size_t i = 0; i <= numTabs; ++i) {
		std::cout << "\t";
	}

	std::cout << tree_[node].data_.key_ << ", " << tree_[node].data_.value_ << std::endl;
	print(tree_[node].leftChild_, ++numTabs);
}

bool AVLTree::find(const int key, const int value) {
	if (!find(tree_[root_], key, value)) {
		std::cerr << "Unable to change value- key not found in the map" << std::endl;
		return false;
	}
	return true;
}

bool AVLTree::find(Node& currNode, const int key, const int value) {
	if (currNode.data_.key_ == key) {
		currNode.data_.value_ = value;
		return true;
	}
	else if (key > currNode.data_.key_) {
		find(tree_[currNode.rightChild_], key, value);
	}
	else if (key < currNode.data_.key_) {
		find(tree_[currNode.leftChild_], key, value);
	}
	else {
		std::cout << "WTF IS GOING OOOOOOOOOOOOOOOOOOON?" << std::endl;
		return false;
	}
}

std::vector<int> AVLTree::findRange(const int lowkey, const int highkey) {
	std::vector<int> keys;
	for (auto it = tree_.begin(); it != tree_.end(); ++it) {
		if (it->data_.key_ <= lowkey && it->data_.key_ >= highkey) {
			keys.push_back(it->data_.key_);
			keys.push_back(it->data_.value_);
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
			currNode.leftChild_ = node.position_;
			node.parent_ = currNode.position_;
			return true;
		}
		else {
			return insertNode(node, tree_[currNode.leftChild_]);
		}
	}
	else if (currNode.data_.key_ < node.data_.key_) {
		if(currNode.rightChild_ == INVALID_NODE) {
			currNode.rightChild_ = node.position_;
			node.parent_ = currNode.position_;
			return true;
		}
		else {
			return insertNode(node, tree_[currNode.rightChild_]);
		}
	}
	return false;
}
