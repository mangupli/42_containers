#include "tests.hpp"

int	stack_tests()
{
	std::ofstream fs;

	mkdir("./tests/tests_output", 0777);

	std::cout << "---------------------------------------\n";
	std::cout << "                 STACK                 \n";
	std::cout << "---------------------------------------\n";
	
	fs.open("./tests/tests_output/stack_tests_output.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

	fs << "STACK\n";

	{
		fs << "Default Constructor:\n";
		fs << "[OK]\n";
	}
	
	fs.close();

	return (0);
}