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
				employees._tree[i]._name << "\n" << std::endl;
			continue;
		}
		std::cout << "Employee: " <<
			employees._tree[i]._name << std::endl;

		std::cout << "Boss: " <<
			employees._tree[employees._tree[i]._parent]._name << "\n" << std::endl;
	}

	std::cout << "Press enter to continue . . . " << std::endl;
	std::cin.get();
	return 0;
}
