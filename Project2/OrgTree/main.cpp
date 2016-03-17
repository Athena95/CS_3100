#include "TreeOrg.h"
#include <iostream>

int main() {

	std::string filename = "employees.txt";

	TreeOrg employees;
	employees.read(filename);

	// employees.addRoot("Boss Man", "Boss");

	std::cout << "Press enter to continue . . . " << std::endl;
	std::cin.get();
	return 0;
}
