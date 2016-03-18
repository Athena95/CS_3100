#include "TreeOrg.h"
#include <iostream>

int main() {

	std::string filename = "employees.txt";

	TreeOrg employees;
	employees.read(filename);

	//employees.addRoot("King of Kings", "Jesus Christ");
	//employees.fire("VP of Software Development");

	employees.printSubTree(11);
	employees.write("Tree.csv");

	std::cout << "Press enter to continue . . . " << std::endl;
	std::cin.get();
	return 0;
}
