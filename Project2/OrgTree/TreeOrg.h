#pragma once
#include "TreeNode.h"
#include <string>

// Krista Vanderhorst
// CS 3100
// TreeOrg Class creates a general tree
class TreeOrg {
public:

	// TreeOrg Constructor
	// Initializes member variables
	TreeOrg();

	// TreeOrg Destructor
	// deletes array of nodes
	~TreeOrg();

	/**
	* @pre- none
	* @post- a new root is added and the old root becomes the new root's child
	* @param title- title of the new root
	* @param name- name of the new root
	* @return nothing
	* O(n)
	*/
	void addRoot(const std::string& title, const std::string& name);

	/**
	* @pre- none
	* @post- the size has been gotten
	* @return- the size of the tree
	* O(1)
	*/
	size_t getSize();

	/**
	* @pre- none
	* @post- the root has been gotten
	* @return a pointer to the root of the tree
	* O(1)
	*/
	TREENODEPTR getRoot();

	/**
	* @pre- node in question must exist
	* @post- the leftmost child of the node has been gotten
	* @param node- the node whos leftmost child we are returning
	* @return a pointer to the leftmost child of the node
	* O(1)
	*/
	TREENODEPTR leftmostChild(TREENODEPTR node);

	/**
	* @pre- node in question must exist
	* @post- the right sibling of the node has been gotten
	* @param node- the node whos right sibling we are returning
	* @return a pointer to the right sibling of the node
	* O(1)
	*/
	TREENODEPTR rightSibling(TREENODEPTR node);

	/**
	* @pre- node in question must exist
	* @post- the subtree has been printed
	* @param subTreeNode- print this node and all its children
	* @return nothing
	* O(n)
	*/
	void printSubTree(TREENODEPTR subTreeNode);

	/**
	* @pre- none
	* @post- the node has either been found or not
	* @param title- title of the node to be found
	* @return a pointer to the node, returns null if not found
	* O(n)
	*/
	TREENODEPTR find(const std::string& title);
	
	/**
	* @pre- none
	* @post- tree of nodes given in filename now exist
	* @param filename- file of data to be read
	* @return true if read successfully, false if not
	* O(n)
	*/
	bool read(const std::string& filename);

	/**
	* @pre- some tree must exist to be printed
	* @post- the data has been written to file
	* @param filename- file to read out to
	* @return nothing
	* O(n)
	*/
	void write(const std::string& filename);

	/**
	* @pre- some tree must exist to be printed
	* @post- the data has been written to file
	* @param node- parent of node to be hired
	* @param newTitle- title of node to be hired
	* @param newName- name of node to be hired
	* @return nothing
	* O(n)
	*/
	void hire(TREENODEPTR node, const std::string& newTitle, const std::string& newName);
	
	/**
	* @pre- none
	* @post- node with title will be fired if exists and not boss
	* @param fornmerTitle- title of node to be fired
	* @return true if node was fired successfully
	* O(n)
	*/
	bool fire(const std::string& formerTitle);

private:

	// Private members
	TreeNode* tree_;
	TREENODEPTR treeRoot_;
	size_t size_, capacity_;

	// Const initial capacity value
	static const size_t INITIAL_CAPACITY = 50;

	// Private Helper Functions
	// Doubles size of the array
	// O(n)
	TreeNode* resize();

	// Returns the child right before target node
	// O(n)
	TREENODEPTR findChild(TREENODEPTR node, TREENODEPTR targetnode);

	// Sets a parent's list of children to point to new parent
	// O(n)
	void promoteChildren(TREENODEPTR newParent, TREENODEPTR endChild);
};
