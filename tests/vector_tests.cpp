#include <iostream>
#include <vector>

#include "vector_tests.hpp"


int vector_tests()
{
	std::fstream	file;
	bool			result;

	mkdir("./tests/tests_output", 0777);

	std::cout << YELLOW << "---------------------------------------\n";
	std::cout << "                 VECTOR                 \n";
	std::cout << "---------------------------------------\n" << RESET;
	
	file.open("./tests/tests_output/vector_tests_output.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

	file << "VECTOR\n";

	{
		file << "------------------------------------------------------------------------\n";
		file << "Default Constructor:\n";
		std::cout << MAGENTA << "Default Constructor:\n" << RESET;


		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, true);
	}


	file.close();

	return 0;
}
