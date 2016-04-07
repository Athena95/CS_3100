#include "AVLTree.h"
#include <iostream>
#include <string>

int main() {

	AVLTree tree;
	size_t numItems = 20;

	for (size_t i = 0; i < numItems; ++i) {
		tree.insert(i, i + 1);
	}

	tree.find(2, 2);
	std::vector<int> rangeVector(tree.findRange(15, 19));
	
	for (auto it = rangeVector.begin(); it != rangeVector.end(); ++it) {
		std::cout << *it << " " << std::endl;
	}
	
	std::cout << tree.getSize() << std::endl;
	tree.print();

	system("pause");
	return 0;
}
