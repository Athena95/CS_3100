#pragma once
#include "TreeNode.h"
#include <string>

class TreeOrg {
public:

	TreeOrg();
	~TreeOrg();

	void addRoot(const std::string& title, const std::string& name);
	int getSize();
	TREENODEPTR getRoot();
	TREENODEPTR leftmostChild(TREENODEPTR node);
	TREENODEPTR rightSibling(TREENODEPTR node);
	void printSubTree(TREENODEPTR subTreeNode);
	TREENODEPTR find(const std::string& title);
	
	bool read(const std::string& filename);
	void write(const std::string& filename);
	void hire(TREENODEPTR node, const std::string& newTitle, const std::string& newName);
	bool fire(const std::string& formerTitle);

	TreeNode* tree_;

private:

	size_t size_, capacity_, treeRoot_;
	static const size_t INITIAL_CAPACITY = 50;

	TreeNode* resize();
	TREENODEPTR findChild(TREENODEPTR node, TREENODEPTR targetnode);
};
