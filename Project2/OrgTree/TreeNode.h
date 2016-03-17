#pragma once
#include <string> 

#define TREENODEPTR size_t
#define TREENULLPTR -1

class TreeNode {
public:

	TreeNode() : name_(""), title_("") {
		TreeNode(name_, title_);
	}

	TreeNode(const std::string& name, const std::string& title) : name_(name), title_(title) {
		setPointers(TREENULLPTR, TREENULLPTR, TREENULLPTR);
	}

	void remove() {
		name_ = "";
		title_ = "";
		setPointers(TREENULLPTR, TREENULLPTR, TREENULLPTR);
	}

	void operator=(const TreeNode& other) {
		name_ = other.name_;
		title_ = other.title_;
		parent_ = other.parent_;
		leftmostChild_ = other.leftmostChild_;
		rightSibling_ = other.rightSibling_;
	}

	void setPointers(TREENODEPTR p, TREENODEPTR lc, TREENODEPTR rs) {
		parent_ = p;
		leftmostChild_ = lc;
		rightSibling_ = rs;
	}

	bool isEmpty() { return name_ == ""; };

	// Data
	std::string name_, title_;

	// Pointers
	TREENODEPTR parent_, leftmostChild_, rightSibling_;
};
