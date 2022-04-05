#include "tests.hpp"
#include "stack_tests.hpp"

int	stack_tests()
{
	std::fstream	file;
	bool			result;

	mkdir("./tests/tests_output", 0777);

	std::cout << "---------------------------------------\n";
	std::cout << "                 STACK                 \n";
	std::cout << "---------------------------------------\n";
	
	file.open("./tests/tests_output/stack_tests_output.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

	file << "STACK\n";

	{
		file << "------------------------------------------------------------------------\n";
		file << "Default Constructor:\n";
		std::cout << MAGENTA << "Default Constructor:\n" << RESET;


		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		result = compare_and_print_stack_results(file, stl_stack, ft_stack);
		
		if (result == true)
			std::cout << GREEN << "[OK]" << RESET;
		else
			std::cout << RED << "[KO]" << RESET;
		file << (result == true ? "[OK]\n" : "[KO]\n");

		std::cout << std::endl;	
	}


	{
		file << "------------------------------------------------------------------------\n";
		file << "Push:\n";
		std::cout << MAGENTA << "Push:\n" << RESET;

		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		stl_stack.push(42);
		ft_stack.push(42);

		result = compare_and_print_stack_results(file, stl_stack, ft_stack);
		
		if (result == true)
			std::cout << GREEN << "[OK]" << RESET;
		else
			std::cout << RED << "[KO]" << RESET;
		file << (result == true ? "[OK]\n" : "[KO]\n");


		stl_stack.push(21);
		ft_stack.push(21);

		result = compare_and_print_stack_results(file, stl_stack, ft_stack);
		
		if (result == true)
			std::cout << GREEN << "[OK]" << RESET;
		else
			std::cout << RED << "[KO]" << RESET;
		file << (result == true ? "[OK]\n" : "[KO]\n");

		std::cout << std::endl;	

		file << "------------------------------------------------------------------------\n";
		file << "Pop:\n";
		std::cout << MAGENTA << "Pop:\n" << RESET;

		stl_stack.pop();
		ft_stack.pop();

		result = compare_and_print_stack_results(file, stl_stack, ft_stack);
		
		if (result == true)
			std::cout << GREEN << "[OK]" << RESET;
		else
			std::cout << RED << "[KO]" << RESET;
		file << (result == true ? "[OK]\n" : "[KO]\n");

		stl_stack.pop();
		ft_stack.pop();

		result = compare_and_print_stack_results(file, stl_stack, ft_stack);
		
		if (result == true)
			std::cout << GREEN << "[OK]" << RESET;
		else
			std::cout << RED << "[KO]" << RESET;
		file << (result == true ? "[OK]\n" : "[KO]\n");
		std::cout << std::endl;	

		file << "------------------------------------------------------------------------\n";
		file << "Size 100000:\n";
		std::cout << MAGENTA << "Size 100000:\n" << RESET;

		for (int i = 0; i < 100000; i++)
        {
            stl_stack.push(i);
            ft_stack.push(i);
        }
		result = compare_and_print_stack_results(file, stl_stack, ft_stack);
		
		if (result == true)
			std::cout << GREEN << "[OK]" << RESET;
		else
			std::cout << RED << "[KO]" << RESET;
		file << (result == true ? "[OK]\n" : "[KO]\n");

				for (int i = 0; i < 100000; i++)
        {
            stl_stack.pop();
            ft_stack.pop();
        }
		result = compare_and_print_stack_results(file, stl_stack, ft_stack);
		
		if (result == true)
			std::cout << GREEN << "[OK]" << RESET;
		else
			std::cout << RED << "[KO]" << RESET;
		file << (result == true ? "[OK]\n" : "[KO]\n");

		std::cout << std::endl;	

	}
	
	file.close();

	return (0);
}