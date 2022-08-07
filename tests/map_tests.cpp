/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:55:16 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/06 18:56:37 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

int	map_tests()
{

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
     
         
    
    return 0;
}