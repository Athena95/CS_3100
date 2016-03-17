#include "TreeOrg.h"
#include <iostream>

int main() {
	std::string filename = "employees.txt";

	TreeOrg employees;
	employees.read(filename);

	// employees.addRoot("Boss Man", "Boss");

	for (size_t i = 0; i < employees.getSize(); ++i) {

		if (i == 0) {
			std::cout << "Head honcho" <<
				employees.tree_[i].name_ << "\n" << std::endl;
			continue;
		}

// TODO- remove access to tree-only for temporary testing purposes
		std::cout << "Employee: " <<
			employees.tree_[i].name_ << std::endl;

		std::cout << "Boss: " <<
			employees.tree_[employees.tree_[i].parent_].name_ << "\n" << std::endl;
	}

	std::cout << "Press enter to continue . . . " << std::endl;
	std::cin.get();
	return 0;
}
