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

# define RESET "\033[0m"
# define FT 24
# define STL 42

template<class T>
bool compare_value(const T& value1, const T& value2)
{
	return (value1 == value2 ? true : false);
}


int	stack_tests();


#endif