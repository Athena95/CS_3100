#include "AVLTree.h"
#include <iostream>
#include <string>

int main() {

	AVLTree tree;
	size_t numItems = 20;

	for (size_t i = 0; i < numItems; ++i) {
		tree.insert(i, i + 1);
	}

	tree.find(6, 50);
	tree.findRange(15, 19);
	tree.getSize();
	tree.print();

	return 0;
}