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
// TODO- print le peoples
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

	TREENODEPTR tempParent = 0;

	if (!in) {
		std::cerr << "Cannot open file" << std::endl;
		return false;
	}

	while (std::getline(in, data)) {
		std::string title, name;
		std::istringstream ss(data);
		getline(ss, title, ',');
		getline(ss, name);

		if (title == ")") {
			tempParent = tree_[tempParent].parent_;
		}
		else {
			if (size_ == 0) {
				addRoot(title, name);
			}
			else {
				hire(tempParent, title, name);
				tempParent = size_ - 1;
			}
		}
	}
	return true;
}

void TreeOrg::write(const std::string& filename) {
	std::ofstream out(filename);
// TODO- write stuff and things to file
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
		TREENODEPTR lastChild = findChild(tree_[parentNode].leftmostChild_, TREENULLPTR);
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

			if (tree_[i].leftmostChild_ != TREENULLPTR) {
				// Rightmost child-bro should point to leftmost child
				TREENODEPTR lastChild = findChild(tree_[tree_[i].parent_].leftmostChild_, TREENULLPTR);
				tree_[lastChild].rightSibling_ = tree_[i].leftmostChild_;

				// Promote Children
				promoteChildren(i, tree_[i].parent_, tree_[i].leftmostChild_);
			}

			if (tree_[i].rightSibling_ != TREENULLPTR && tree_[tree_[i].parent_].leftmostChild_ != i) {
				// Get child before the guy we're firing
				// Set his right sibling to the guy we're firing's right sibling
				TREENODEPTR childBeforeNode = findChild(tree_[tree_[i].parent_].leftmostChild_, i);
				tree_[childBeforeNode].rightSibling_ = tree_[i].rightSibling_;
			}
			else if (tree_[tree_[i].parent_].leftmostChild_ == i) {
				tree_[tree_[i].parent_].leftmostChild_ = tree_[i].rightSibling_;
			}

			tree_[i].remove();	// "Destructor" for Node

			// If we didn't just delete the last node,
			// put last node in array into deleted spot
			if (!tree_[size_ - 1].isEmpty()) {

				// move last node
				tree_[i] = tree_[size_ - 1];

				// point children to new position
				promoteChildren(size_ - 1, i, tree_[size_ - 1].leftmostChild_);

				// anything that points to the last node
				// will now point to its new position
				for (size_t j = 0; j < size_; ++j) {
					if (tree_[j].rightSibling_ == size_ - 1) {
						tree_[j].rightSibling_ = i;
					}
					if (tree_[j].leftmostChild_ == size_ - 1) {
						tree_[j].leftmostChild_ = i;
					}
				}
			}
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

TREENODEPTR TreeOrg::findChild(TREENODEPTR node, TREENODEPTR targetnode) {
	if (tree_[node].rightSibling_ == targetnode) {
		return node;
	}
	else {
		return findChild(tree_[node].rightSibling_, targetnode);
	}
}

void TreeOrg::promoteChildren(TREENODEPTR parent, TREENODEPTR newParent, TREENODEPTR currentChild) {

	tree_[currentChild].parent_ = newParent;

	if (currentChild == TREENULLPTR) {
		return;
	}
	else {
		return promoteChildren(parent, newParent, tree_[currentChild].rightSibling_);
	}
}
