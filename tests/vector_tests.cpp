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

	{
		file << "------------------------------------------------------------------------\n";
		file << "Push_back:\n";
		std::cout << MAGENTA << "Push_back:\n" << RESET;


		std::vector<std::string> stl_vector;
		ft::vector<std::string> ft_vector;

		for(int i = 0; i < 6; ++i){
			stl_vector.push_back("test");
			ft_vector.push_back("test");
		}

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, true);

		file << "------------------------------------------------------------------------\n";
		file << "Copy constructor:\n";
		std::cout << MAGENTA << "Copy constructor:\n" << RESET;


		std::vector<std::string> stl_vector_copy(stl_vector);
		ft::vector<std::string> ft_vector_copy(ft_vector);

		result = compare_and_print_vector_results(file, stl_vector_copy, ft_vector_copy);
		print_result_cout(result, true);

		file << "------------------------------------------------------------------------\n";
		file << "Pop_back:\n";
		std::cout << MAGENTA << "Pop_back:\n" << RESET;

		for(int i = 0; i < 4; ++i){
			stl_vector_copy.pop_back();
			ft_vector_copy.pop_back();
		}

		result = compare_and_print_vector_results(file, stl_vector_copy, ft_vector_copy);
		print_result_cout(result, true);

		file << "------------------------------------------------------------------------\n";
		file << "Assignment operator:\n";
		std::cout << MAGENTA << "Assignment operator:\n" << RESET;

		stl_vector_copy = stl_vector;
		ft_vector_copy = ft_vector;

		result = compare_and_print_vector_results(file, stl_vector_copy, ft_vector_copy);
		print_result_cout(result, true);

	}

	std::vector<int> v1;
	ft::vector<int> v2;

	for(int i = 0; i < 6; ++i) v1.push_back(i);
	for(int i = 0; i < 6; ++i) v2.push_back(i);

	std::vector<int> big1;
	ft::vector<int> big2;

	for(int i = 0; i < 1000; ++i) v1.push_back(i);
	for(int i = 0; i < 1000; ++i) v2.push_back(i);
	
	{

		file << "------------------------------------------------------------------------\n";
		file << "Assign:\n";
		std::cout << MAGENTA << "Assign:\n" << RESET;

		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;

		file << "1: \n";

		stl_vector.assign(v1.begin(), v1.begin());
		ft_vector.assign(v2.begin(), v2.begin());

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, false);

		file << "2: \n";

		stl_vector.assign(v1.begin(), v1.end());
		ft_vector.assign(v2.begin(), v2.end());

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, false);

		file << "3: \n";

		stl_vector.assign(v1.begin(), v1.begin());
		ft_vector.assign(v2.begin(), v2.begin());

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, false);
		
		file << "4: \n";

		stl_vector.assign(big1.begin(), big1.end());
		ft_vector.assign(big2.begin(), big2.end());

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, false);

		file << "5: \n";

		stl_vector.assign(0, 123456);
		ft_vector.assign(0, 123456);

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, false);

		file << "6: \n";

		stl_vector.assign(123456, 123456);
		ft_vector.assign(123456, 123456);

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, true);

	}


	file.close();

	return 0;
}
