#include "AVLTree.h"
#include <iostream>
#include <string>

int main() {

	AVLTree tree;
	size_t numItems = 20;

	tree.insert(2, 5);
	tree.insert(1, 700);
	tree.insert(9, 13);
	tree.insert(4, 10);
	tree.insert(1, 80);
	tree.insert(90, 110);
	tree.insert(55, 30);
	tree.insert(7, 83);
	tree.insert(43, 18);
	//tree.insert(1, 1);
	//tree.insert(2, 2);
	//tree.insert(3, 3);

	int myInt = 0;
	tree.find(55, myInt);

	std::cout << "Using key 55, I found: " << myInt << std::endl;
	std::vector<int> rangeVector(tree.findRange(50, 100));
	
	for (auto it = rangeVector.begin(); it != rangeVector.end(); ++it) {
		std::cout << *it << " " << std::endl;
	}
	
	std::cout << tree.getSize() << std::endl;
	tree.print();

	std::cout << tree.getHeight() << std::endl;

	system("pause");
	return 0;
}
