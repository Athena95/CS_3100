#include "TreeOrg.h"
#include <fstream>
#include <sstream>
#include <iostream>

TreeOrg::TreeOrg() : size_( 0 ), capacity_( INITIAL_CAPACITY ), treeRoot_( 0 ) {
	tree_ = new TreeNode[capacity_];
}

TreeOrg::~TreeOrg() {
	delete[](tree_);
}

void TreeOrg::addRoot(const std::string& title, const std::string& name) {
	hire(TREENULLPTR, title, name);
}

int TreeOrg::getSize() {
	return size_;
}

TREENODEPTR TreeOrg::getRoot() {
	return treeRoot_;
}

TREENODEPTR TreeOrg::leftmostChild(TREENODEPTR node) {
	return tree_[node].leftmostChild_;
}

TREENODEPTR TreeOrg::rightSibling(TREENODEPTR node) {
	return tree_[node].rightSibling_;
}

void TreeOrg::printSubTree(TREENODEPTR subTreeNode) {
	// TODO- recursive function
	std::cout << "This prints people!" << std::endl;
}

TREENODEPTR TreeOrg::find(const std::string& title) {
	for (size_t i = 0; i < size_; ++i) {
		if (tree_[i].title_ == title) {
			return i;
		}
	}

	std::cerr << "Cannot find the " << title << " in the company!" << std::endl;
	return TREENULLPTR;
}

bool TreeOrg::read(const std::string& filename) {
	std::ifstream in(filename);
	std::string data;
	bool endSubtree = false;

	while(std::getline(in, data)) {
		std::string title, name;
		std::istringstream ss(data);
		getline(ss, title, ',');
		getline(ss, name);

		if (title != ")") {
			if (endSubtree) {
				getline(ss, title, ',');
				getline(ss, name);

				hire(tree_[size_ - 1].parent_, title, name);
				endSubtree = false;
			}
			else {
				hire(size_ - 1, title, name);
			}
		}
		else if (title == ")") {
			if (size_ != 0) {
				endSubtree = true;
			}
		}
		else if (size_ == 0) {
			addRoot(title, name);
		}
	}
	
	return false;
}

void TreeOrg::write(const std::string& filename) {
	std::ofstream out(filename);
	// TODO- write stuff and things
}

void TreeOrg::hire(TREENODEPTR parentNode, const std::string& newTitle, const std::string& newName) {

	TREENODEPTR nodePtr = size_;
	TreeNode node(newName, newTitle);
	node.setPointers(parentNode, TREENULLPTR, TREENULLPTR);
	tree_[nodePtr] = node;

	++size_;

	// resize as soon as capacity is reached
	if (size_ == capacity_) {
		tree_ = resize();
	}
	
	if (parentNode == TREENULLPTR) {
		if (nodePtr != 0) {
			tree_[treeRoot_].parent_ = nodePtr;
			node.leftmostChild_ = treeRoot_;
		}
		treeRoot_ = nodePtr;
	}
	else if (tree_[parentNode].leftmostChild_ == TREENULLPTR) {
		tree_[parentNode].leftmostChild_ = nodePtr;
	}
	else {
		TREENODEPTR lastChild = findRightmostChild(tree_[parentNode].leftmostChild_, TREENULLPTR);
		tree_[lastChild].rightSibling_ = nodePtr;	
	}
}

bool TreeOrg::fire(const std::string& formerTitle) {
	if (tree_[treeRoot_].title_ == formerTitle) {
		std::cerr << "You can't fire the boss!" << std::endl;
		return false;
	}
	
	for (size_t i = 0; i < size_; ++i) {
		if (tree_[i].title_ == formerTitle) {
			
			// If not the only child...
			if (tree_[tree_[i].parent_].leftmostChild_ != i) {

				// Get child before the guy we're firing
				// Set his right sibling to the guy we're firing's right sibling
				TREENODEPTR childBeforeNode = findRightmostChild(tree_[tree_[i].parent_].leftmostChild_, i);
				tree_[childBeforeNode].rightSibling_ = tree_[i].rightSibling_;

			}
			// Set the parent's leftmostChild to the first child of the fired guy
			else {
				tree_[tree_[i].parent_].leftmostChild_ = tree_[i].leftmostChild_;
			}

// TODO- we don't want wasted space! 
// Move last guy in the array to the empty spot, and fix pointers accordingly...
// Could get tricky...

			--size_;
			return true;
		}
	}

	std::cerr << "Unable to find the " << formerTitle << " in the company!" << std::endl;
	return false;
}

TreeNode* TreeOrg::resize() {
	capacity_ *= 2;
	TreeNode* tree = new TreeNode[capacity_];

	for (size_t i = 0; i < size_; ++i) {
		tree[i] = tree_[i];
	}

	delete[](tree_);
	return tree;
}

TREENODEPTR TreeOrg::findRightmostChild(TREENODEPTR node, TREENODEPTR targetnode) {
	if (tree_[node].rightSibling_ == targetnode) {
		return node;
	}
	else {
		return findRightmostChild(tree_[node].rightSibling_, targetnode);
	}
}
