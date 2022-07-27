/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:40:16 by mspyke            #+#    #+#             */
/*   Updated: 2022/07/27 22:02:14 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include "stack_tests.hpp"

int	stack_tests()
{
	std::fstream	file;
	bool			result;

	mkdir("./tests/tests_output", 0777);

	std::cout << YELLOW << "---------------------------------------\n";
	std::cout << "                 STACK                 \n";
	std::cout << "---------------------------------------\n" << RESET;
	
	file.open("./tests/tests_output/stack_tests_output.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

	file << "STACK\n";

	{
		file << "------------------------------------------------------------------------\n";
		file << "Default Constructor:\n";
		std::cout << MAGENTA << "Default Constructor:\n" << RESET;


		std::stack<int> stl_stack;
		ft::stack<int> ft_stack;

		result = compare_and_print_stack_results(file, stl_stack, ft_stack);
		print_result_cout(result, true);
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
		print_result_cout(result, false);
		

		stl_stack.push(21);
		ft_stack.push(21);

		result = compare_and_print_stack_results(file, stl_stack, ft_stack);
		print_result_cout(result, true);

		file << "------------------------------------------------------------------------\n";
		file << "Pop:\n";
		std::cout << MAGENTA << "Pop:\n" << RESET;

		stl_stack.pop();
		ft_stack.pop();

		result = compare_and_print_stack_results(file, stl_stack, ft_stack);
		print_result_cout(result, false);

		stl_stack.pop();
		ft_stack.pop();

		result = compare_and_print_stack_results(file, stl_stack, ft_stack);
		print_result_cout(result, true);

		file << "------------------------------------------------------------------------\n";
		file << "Size 100000:\n";
		std::cout << MAGENTA << "Size 100000:\n" << RESET;

		for (int i = 0; i < 100000; i++)
        {
            stl_stack.push(i);
            ft_stack.push(i);
        }
		result = compare_and_print_stack_results(file, stl_stack, ft_stack);
		print_result_cout(result, false);
		

		for (int i = 0; i < 100000; i++)
        {
            stl_stack.pop();
            ft_stack.pop();
        }
		result = compare_and_print_stack_results(file, stl_stack, ft_stack);
		print_result_cout(result, true);

	}

	{
		file << "------------------------------------------------------------------------\n";
		file << "Copy Constructor:\n";
		std::cout << MAGENTA << "Copy Constructor:\n" << RESET;


		std::stack<std::string> stl_stack;
		ft::stack<std::string> ft_stack;

		for (int i = 0; i < 5; i++)
        {
            stl_stack.push("42");
            ft_stack.push("42");
        }

		std::stack<std::string> stl_stack_copy(stl_stack);
		ft::stack<std::string> ft_stack_copy(ft_stack);

		result = compare_and_print_stack_results(file, stl_stack_copy, ft_stack_copy);
		print_result_cout(result, true);
	}

	{
		file << "------------------------------------------------------------------------\n";
		file << "Comparison operators:\n";
		std::cout << MAGENTA << "Comparison operators:\n" << RESET;

		std::stack<int> stl_stack1;
		ft::stack<int> ft_stack1;
		std::stack<int> stl_stack2;
		ft::stack<int> ft_stack2;

		//-----------------------------------------------------------------
		std::cout << MAGENTA << "==\n" << RESET;
		file << "==\n";

		result = (stl_stack1==stl_stack2) == (ft_stack1==ft_stack2);
		file << (result == true ? "[OK]\n" : "[KO]\n");
		print_result_cout(result, false);

		for (int i = 0; i < 5; i++)
        {
            stl_stack1.push(i);
            ft_stack1.push(i);
			stl_stack2.push(i);
            ft_stack2.push(i);
        }

		result = (stl_stack1==stl_stack2) == (ft_stack1==ft_stack2);
		file << (result == true ? "[OK]\n" : "[KO]\n");
		print_result_cout(result, false);

		ft_stack1.pop();
		stl_stack1.pop();

		result = (stl_stack1==stl_stack2) == (ft_stack1==ft_stack2);
		file << (result == true ? "[OK]\n" : "[KO]\n");
		print_result_cout(result, true);

		//---------------------------------------------------------------------
		std::cout << MAGENTA << "!=\n" << RESET;
		file << "!=\n";

		result = (stl_stack1!=stl_stack2) == (ft_stack1!=ft_stack2);
		file << (result == true ? "[OK]\n" : "[KO]\n");
		print_result_cout(result, false);

		ft_stack1.push(42);
		stl_stack1.push(42);

		result = (stl_stack1!=stl_stack2) == (ft_stack1!=ft_stack2);
		file << (result == true ? "[OK]\n" : "[KO]\n");
		print_result_cout(result, false);

		ft_stack1.top() = 4;
		stl_stack1.top() = 4;

		result = (stl_stack1!=stl_stack2) == (ft_stack1!=ft_stack2);
		file << (result == true ? "[OK]\n" : "[KO]\n");
		print_result_cout(result, true);

		//-----------------------------------------------------------
		std::cout << MAGENTA << "< and <=\n" << RESET;
		file << "< and <=\n";

		ft_stack1.top() = 42;
		stl_stack1.top() = 42;

		result = (stl_stack1<stl_stack2) == (ft_stack1<ft_stack2);
		file << (result == true ? "[OK]\n" : "[KO]\n");
		print_result_cout(result, false);

		ft_stack1.pop();
		stl_stack1.pop();
	
		result = (stl_stack1<=stl_stack2) == (ft_stack1<=ft_stack2);
		file << (result == true ? "[OK]\n" : "[KO]\n");
		print_result_cout(result, true);

		//---------------------------------------------------------
		std::cout << MAGENTA << "> and >=\n" << RESET;
		file << "> and >=\n";

		ft_stack1.push(42);
		stl_stack1.push(42);

		result = (stl_stack1>stl_stack2) == (ft_stack1>ft_stack2);
		file << (result == true ? "[OK]\n" : "[KO]\n");
		print_result_cout(result, false);

		ft_stack1.pop();
		stl_stack1.pop();
	
		result = (stl_stack1>=stl_stack2) == (ft_stack1>=ft_stack2);
		file << (result == true ? "[OK]\n" : "[KO]\n");
		print_result_cout(result, true);
		
	}

	{
		file << "------------------------------------------------------------------------\n";
		file << "Constant:\n";
		std::cout << MAGENTA << "Constant:\n" << RESET;

		std::vector<int> v(5, 42);
		
		const ft::stack<int> ft_stack(v);
		const std::stack<int, std::vector<int> > stl_stack(v);

		result = (stl_stack.top()) == (ft_stack.top());
		file << (result == true ? "[OK]\n" : "[KO]\n");
		print_result_cout(result, true);
		
		
	}

	file.close();

	return (0);
}