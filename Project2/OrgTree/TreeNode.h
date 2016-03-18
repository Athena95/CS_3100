#pragma once
#include <string> 

#define TREENODEPTR size_t
#define TREENULLPTR -1

// TreeNode Class
// All data and functions are public
class TreeNode {
public:

	// Empty Constructor
	TreeNode() : name_(""), title_("") {
		TreeNode(name_, title_);
	}

	// Paramaterized Constructor
	TreeNode(const std::string& name, const std::string& title) : name_(name), title_(title) {
		setPointers(TREENULLPTR, TREENULLPTR, TREENULLPTR);
	}

	// Clears all data for node
	void remove() {
		name_ = "";
		title_ = "";
		setPointers(TREENULLPTR, TREENULLPTR, TREENULLPTR);
	}

	// Overloaded = operator
	void operator=(const TreeNode& other) {
		name_ = other.name_;
		title_ = other.title_;
		parent_ = other.parent_;
		leftmostChild_ = other.leftmostChild_;
		rightSibling_ = other.rightSibling_;
	}

	// Sets the pointers of the node
	void setPointers(TREENODEPTR p, TREENODEPTR lc, TREENODEPTR rs) {
		parent_ = p;
		leftmostChild_ = lc;
		rightSibling_ = rs;
	}

	// Returns true if empty
	bool isEmpty() { return name_ == ""; };

	// Data
	std::string name_, title_;

	// Pointers
	TREENODEPTR parent_, leftmostChild_, rightSibling_;
};
