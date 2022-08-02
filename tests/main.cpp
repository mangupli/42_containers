/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:40:32 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/02 15:30:28 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include <deque>

#include "../containers/stack.hpp"
#include "tests.hpp"

void print_result_cout(const bool & result, const bool & new_line_needed)
{
	if (result == true)
		std::cout << GREEN << "[OK]" << RESET;
	else
		std::cout << RED << "[KO]" << RESET;

	if (new_line_needed)
		std::cout << std::endl;
}

void print_result_file(std::fstream &file, const bool & result){
	file << (result == true ? "[OK]\n" : "[KO]\n");
}


int main()
{
	stack_tests();
	vector_tests();
	return (0);
}
