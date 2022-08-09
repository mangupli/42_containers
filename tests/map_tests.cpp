/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:55:16 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/09 18:39:05 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_tests.hpp"


int	map_tests()
{

    std::fstream	file;
	bool			result = true;

	mkdir("./tests/tests_output", 0777);

	std::cout << YELLOW << "---------------------------------------\n";
	std::cout << "                  MAP                  \n";
	std::cout << "---------------------------------------\n" << RESET;
	
	file.open("./tests/tests_output/map_tests_output.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

	file << "MAP\n";

    {
		file << "------------------------------------------------------------------------\n";
		file << "Default Constructor:\n";
		std::cout << MAGENTA << "Default Constructor:\n" << RESET;


		std::map<int, int> stl_map;
		ft::map<int, int> ft_map;

		result = compare_and_print_map_results(file, stl_map, ft_map);
		print_result_cout(result, false);

		ft::map<int, std::string> const ft_map_c;
		std::map<int, std::string> const stl_map_c;

		result = compare_and_print_map_results(file, stl_map_c, ft_map_c);
		print_result_cout(result, true);
	}

    {
		file << "------------------------------------------------------------------------\n";
		file << "Bounds:\n";
		std::cout << MAGENTA << "Bounds:\n" << RESET;
        
        typedef std::map<int, foo<int> >::value_type stl_value;
        typedef ft::map<int, foo<int> >::value_type ft_value;

		std::map<int, int> stl_map;
		ft::map<int, int> ft_map;

		result = compare_and_print_map_results(file, stl_map, ft_map);
		print_result_cout(result, false);

	}


/*
    ft::map<int, int> test;
    const ft::pair<int, int> pair(42, 42);
    
    test.insert(pair);
    for(int i = 100; i > 0; i -=15 )
    {
        test.insert(ft::pair<int, int>(i*5, 42));
    }
     ft::map<int, int>::iterator it = test.begin();

     for( ; it != test.end(); ++it){
        std::cout << it->first << std::endl;
     }


    std::map<int, int> test1;
    const std::pair<int, int> pair1(42, 42);
    
    test1.insert(pair1);
    for(int i = 100; i > 0; i -=15 )
    {
        test1.insert(std::pair<int, int>(i*5, 42));
    }
     std::map<int, int>::iterator it1 = test1.begin();

     for( ; it1 != test1.end(); ++it1){
        std::cout << it1->first << std::endl;
     }
     */
         
    file.close();

    return 0;
}