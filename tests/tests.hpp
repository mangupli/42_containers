/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:44:25 by mspyke            #+#    #+#             */
/*   Updated: 2022/07/28 00:06:26 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_HPP
# define TESTS_HPP

# include <stack>
# include <vector>
# include <list>
# include <deque>
# include <iostream>
# include <fstream>
# include <sys/stat.h>


# include "../containers/stack.hpp"

# define RED	"\033[31;1m"
# define GREEN	"\033[32;1m"
# define MAGENTA "\033[35;1m"
# define YELLOW "\033[33;1m"

# define RESET "\033[0m"
# define FT 24
# define STL 42

template<class T>
bool compare_value(const T& value1, const T& value2)
{
	return (value1 == value2 ? true : false);
}

void print_result_cout(const bool & result, const bool & new_line_needed);


int	stack_tests();
int	vector_tests();


#endif /*TESTS.HPP*/