/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:40:37 by mspyke            #+#    #+#             */
/*   Updated: 2022/07/27 21:58:50 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_TESTS_H
#define STACK_TESTS_H

#include "tests.hpp"

template <class T>
bool	compare_content(
	std::stack<T> stl_stack,
	ft::stack<T> ft_stack
)
{
	while(stl_stack.size()!=0 && ft_stack.size()!=0)
	{
		if(ft_stack.top() != stl_stack.top())
			return (false);
		ft_stack.pop();
        stl_stack.pop();
	}
	return (true);
}

template<class T>
void	print_attributes(
	std::fstream &file,
	std::stack<T> stl_stack,
	ft::stack<T> ft_stack
)
{
	file << "------------------------------------------------------------------------\n";
	file << "STL:\n";
	file << "Empty       : " << stl_stack.empty()  << std::endl;
    file << "Size        : " << stl_stack.size() << std::endl;
    file << "Content     : [";

    int count = 0;
	while (stl_stack.size() != 0 && count < 10)
    {
        ++count;
		file << stl_stack.top();
        stl_stack.pop();
        if (stl_stack.size() != 0)
            file << ", ";
    }
	if (stl_stack.size() > count)
	 	  file << "...";
    file << "]\n";

    file << std::endl;

    file << "FT : \n";
	file << "Empty       : " << ft_stack.empty()  << std::endl;
    file << "Size        : " << ft_stack.size() << std::endl;

    file << "Content     : [";

	count = 0;
    while (ft_stack.size() != 0 && count < 10)
    {
        ++count;
		file << ft_stack.top();
        ft_stack.pop();
        if (ft_stack.size() != 0)
            file << ", ";
    }
	if (stl_stack.size() > count)
	 	  file << "...";
    file << "]\n";

	file << "------------------------------------------------------------------------\n";
}


template <class T>
bool 	compare_and_print_stack_results(
	std::fstream &file,
	std::stack<T> stl_stack,
	ft::stack<T> ft_stack
)
{

	bool result = true;

	bool check_empty = compare_value(stl_stack.empty(), ft_stack.empty());
	bool check_size = compare_value(stl_stack.size(), ft_stack.size());
	bool check_content = compare_content(stl_stack, ft_stack);
	print_attributes(file, stl_stack, ft_stack);

	if(check_empty == false || check_size == false || check_content == false)
		result = false;

	file << (result == true ? "[OK]\n" : "[KO]\n");

	return result;
}


#endif /* STACK_TESTS_H*/
