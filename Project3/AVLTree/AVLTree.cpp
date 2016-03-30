#include "AVLTree.h"
#include <iostream>
#include <string>	

AVLTree::AVLTree() : height_(0), root_(INVALID_NODE) {}

bool AVLTree::insert(const int key, const int value) {
	Node node(key, value);
	tree_.push_back(node);

	if (root_ == INVALID_NODE) {
		root_ = tree_.size() - 1;
		return true;
	}
	else {
		if (!insertNode(node, tree_[root_])) {
			tree_.pop_back();
			return false;
		}
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
	print(root_);
}

void AVLTree::print(const size_t node) {
	if (node == INVALID_NODE) {
		return;
	}
	
	print(tree_[node].rightChild_);
	std::cout << tree_[node].data_.key_ << ", " << tree_[node].data_.value_ << std::endl;
	print(tree_[node].leftChild_);
}

bool AVLTree::find(const int key, const int value) {
	for (auto it = tree_.begin(); it != tree_.end(); ++it) {
		if (it->data_.key_ == key) {
			it->data_.value_ = value;
			return true;
		}
	}

	std::cerr << "Unable to add value- key not found in the map" << std::endl;
	return false;
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
	if (currNode.data_.value_ == node.data_.value_) {
		return false;
	}
	else if (currNode.data_.value_ > node.data_.value_) {
		if (currNode.leftChild_ == NULL) {
			currNode.leftChild_ = tree_.size() - 1;
			node.parent_ = tree_[currNode.parent_].leftChild_;
			return true;
		}
		else {
			return insertNode(node, tree_[currNode.leftChild_]);
		}
	}
	else if (currNode.data_.value_ < node.data_.value_) {
		if(currNode.rightChild_ == NULL) {
			currNode.rightChild_ = tree_.size() - 1;
			node.parent_ = tree_[currNode.parent_].rightChild_;
			return true;
		}
		else {
			return insertNode(node, tree_[currNode.rightChild_]);
		}
	}
	return false;
}
