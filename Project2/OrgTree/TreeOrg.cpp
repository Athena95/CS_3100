#include "TreeOrg.h"
#include <fstream>
#include <sstream>
#include <iostream>

TreeOrg::TreeOrg() : _size( 0 ), _capacity( INITIAL_CAPACITY ), _treeRoot( 0 ) {
	_tree = new TreeNode[_capacity];
}

TreeOrg::~TreeOrg() {
	delete[](_tree);
}

void TreeOrg::addRoot(const std::string& title, const std::string& name) {
	hire(TREENULLPTR, title, name);
}

int TreeOrg::getSize() {
	return _size;
}

TREENODEPTR TreeOrg::getRoot() {
	return _treeRoot;
}

TREENODEPTR TreeOrg::leftmostChild(TREENODEPTR node) {
	return _tree[node]._leftmostChild;
}

TREENODEPTR TreeOrg::rightSibling(TREENODEPTR node) {
	return _tree[node]._rightSibling;
}

void TreeOrg::printSubTree(TREENODEPTR subTreeNode) {
	// TODO- recursive function
	std::cout << "This prints people!" << std::endl;
}

TREENODEPTR TreeOrg::find(const std::string& title) {
	for (size_t i = 0; i < _size; ++i) {
		if (_tree[i]._title == title) {
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

				hire(_tree[_size - 1]._parent, title, name);
				endSubtree = false;
			}
			else {
				hire(_size - 1, title, name);
			}
		}
		else if (title == ")") {
			if (_size != 0) {
				endSubtree = true;
			}
		}
		else if (_size == 0) {
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

	TREENODEPTR nodePtr = _size;
	TreeNode node(newName, newTitle);
	node.setPointers(parentNode, TREENULLPTR, TREENULLPTR);
	_tree[nodePtr] = node;

	++_size;

	// resize as soon as capacity is reached
	if (_size == _capacity) {
		_tree = resize();
	}
	
	if (parentNode == TREENULLPTR) {
		if (nodePtr != 0) {
			_tree[_treeRoot]._parent = nodePtr;
			node._leftmostChild = _treeRoot;
		}
		_treeRoot = nodePtr;
	}
	else if (_tree[parentNode]._leftmostChild == TREENULLPTR) {
		_tree[parentNode]._leftmostChild = nodePtr;
	}
	else {
		TREENODEPTR lastChild = findChild(parentNode);
		_tree[lastChild]._rightSibling = nodePtr;	
	}
}

bool TreeOrg::fire(const std::string& formerTitle) {
	if (_tree[_treeRoot]._title == formerTitle) {
		std::cerr << "You can't fire the boss!" << std::endl;
		return false;
	}

	for (size_t i = 0; i < _size; ++i) {
		if (_tree[i]._title == formerTitle) {
			
			_tree[_tree[i]._parent]._leftmostChild = _tree[i]._rightSibling;

			--_size;
			return true;
		}
	}

	std::cerr << "Unable to find the " << formerTitle << " in the company!" << std::endl;
	return false;
}

TreeNode* TreeOrg::resize() {
	_capacity *= 2;
	TreeNode* tree = new TreeNode[_capacity];

	for (size_t i = 0; i < _size; ++i) {
		tree[i] = _tree[i];
	}

	delete[](_tree);
	return tree;
}

TREENODEPTR TreeOrg::findChild(TREENODEPTR node) {
	if (_tree[node]._rightSibling == TREENULLPTR) {
		return node;
	}
	else {
		return findChild(_tree[node]._leftmostChild);
	}
}
