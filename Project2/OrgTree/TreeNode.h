#pragma once
#include <string> 

#define TREENODEPTR size_t
#define TREENULLPTR -1

class TreeNode {
public:

	TreeNode() : _name(""), _title("") {
		TreeNode(_name, _title);
	}

	TreeNode(const std::string& name, const std::string& title) : _name(name), _title(title) {
		setPointers(TREENULLPTR, TREENULLPTR, TREENULLPTR);
	}

	~TreeNode() {}

	void operator=(const TreeNode& other) {
		_name = other._name;
		_title = other._title;
		_parent = other._parent;
		_leftmostChild = other._leftmostChild;
		_rightSibling = other._rightSibling;
	}

	void setPointers(TREENODEPTR p, TREENODEPTR lc, TREENODEPTR rs) {
		_parent = p;
		_leftmostChild = lc;
		_rightSibling = rs;
	}

	bool isEmpty() { return _name == ""; };

	// Data
	std::string _name, _title;

	// Pointers
	TREENODEPTR _parent, _leftmostChild, _rightSibling;
};
