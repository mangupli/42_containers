/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:55:16 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/10 16:52:54 by mspyke           ###   ########.fr       */
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
		file << "Copy contructors:\n";
		std::cout << MAGENTA << "Copy contructors:\n" << RESET;

        typedef int type1;
        typedef int type2;
        typedef std::pair<type1, type2> std_pair_type;
        typedef ft::pair<type1, type2> ft_pair_type;

        size_t vector_size = 7;

        //----range contructor-----
        
        std::vector<std_pair_type> std_vector;
	   for (unsigned int i = 0; i < vector_size; ++i)
		    std_vector.push_back(std_pair_type(vector_size - i, i));
            
        std::map<type1, type2> std_map(std_vector.begin(), std_vector.end());

        ft::vector<ft_pair_type> ft_vector;
	    for (unsigned int i = 0; i < vector_size; ++i)
		    ft_vector.push_back(ft_pair_type(vector_size - i, i));

        ft::map<type1, type2> ft_map(ft_vector.begin(), ft_vector.end());

        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        //----copy constructor from the range-----
        
       
        
        typename std::map<type1, type2>::iterator std_it = std_map.begin();
        typename std::map<type1, type2>::iterator std_ite = std_map.end();

         std::map<type1, type2> std_map_range(std_it, --(--std_ite));

	    for (int i = 0; std_it != std_ite; ++std_it)
		    std_it->second = ++i * 5;

        typename ft::map<type1, type2>::iterator ft_it = ft_map.begin();
        typename ft::map<type1, type2>::iterator ft_ite = ft_map.end();

        ft::map<type1, type2> ft_map_range(ft_it, --(--ft_ite));

	    for (int i = 0; ft_it != ft_ite; ++ft_it)
		    ft_it->second = ++i * 5;


        result = compare_and_print_map_results(file, std_map_range, ft_map_range);
		print_result_cout(result, false);

        //--------copy constuctor-------


        ft::map<type1, type2> ft_map_copy(ft_map_range);  
        std::map<type1, type2> std_map_copy(std_map_range);

        result = compare_and_print_map_results(file, std_map_copy, ft_map_copy);
		print_result_cout(result, true);

        file << "------------------------------------------------------------------------\n";
		file << "Assignment operator:\n";
		std::cout << MAGENTA << "Assignment operator:\n" << RESET;

        std_it = std_map_range.begin(); std_ite = --(--std_map_range.end());
        for (int i = 0; std_it != std_ite; ++std_it)
		    std_it->second = ++i * 7;  
            
        ft_it = ft_map_range.begin(); ft_ite = --(--ft_map_range.end());
        for (int i = 0; ft_it != ft_ite; ++ft_it)
		    ft_it->second = ++i * 7; 
            
        ft_map = ft_map_copy;
        std_map = std_map_copy;

        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);
        
        ft_map_copy = ft_map_range;
        std_map_copy = std_map_range;
        
        result = compare_and_print_map_results(file, std_map_copy, ft_map_copy);
		print_result_cout(result, false);          
                    
	    ft_map_range.clear();
        std_map_range.clear();
        result = compare_and_print_map_results(file, std_map_copy, ft_map_copy);
		print_result_cout(result, true); 

        file << "------------------------------------------------------------------------\n";
		file << "Comparison operators:\n";
		std::cout << MAGENTA << "Comparison operators:\n" << RESET;

        result = map_comp_operators(std_map, std_map, ft_map, ft_map);
        print_result_cout(result, false);
        
        result = map_comp_operators(std_map, std_map_range, ft_map, ft_map_range);
        print_result_cout(result, true);
		

        file << "------------------------------------------------------------------------\n";
		file << "Swap:\n";
		std::cout << MAGENTA << "Swap:\n" << RESET;

        ft::swap(ft_map, ft_map_range);
        std::swap(std_map, std_map_range);
        
        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);
        
        result = compare_and_print_map_results(file, std_map_range, ft_map_range);
		print_result_cout(result, true); 
		
	}

    {

        file << "------------------------------------------------------------------------\n";
		file << "Insert:\n";
		std::cout << MAGENTA << "Insert:\n" << RESET;

        typedef int type1;
        typedef std::string type2;
        
        typedef std::pair<type1, type2> std_pair_type;
        typedef ft::pair<type1, type2> ft_pair_type;

        typedef std::map<type1, type2>::iterator std_iterator;
        typedef ft::map<type1, type2>::iterator ft_iterator;
        
        std::pair<std_iterator, bool> std_res;
        ft::pair<ft_iterator, bool> ft_res;

        std::map<type1, type2> std_map;              
        ft::map<type1, type2> ft_map;

        
       std_res = std_map.insert(std_pair_type(42, "lisa"));;
       ft_res = ft_map.insert(ft_pair_type(42, "lisa"));
    
        //true
       result = (std_res.second == ft_res.second) && \
                (std_res.first->first == ft_res.first->first) && \
                (std_res.first->second == ft_res.first->second);

        result = result && compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        std_res = std_map.insert(std_pair_type(42, "lol"));;
        ft_res = ft_map.insert(ft_pair_type(42, "lol"));
    
        //false
       result = (std_res.second == ft_res.second) && \
                (std_res.first->first == ft_res.first->first) && \
                (std_res.first->second == ft_res.first->second);

        result = result && compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        ft_map.insert(ft_pair_type(14, "meow"));
        ft_map.insert(ft_pair_type(17, "so smart"));
        ft_map.insert(ft_pair_type(15, "abc"));
        ft_map.insert(ft_pair_type(18, "zhopa"));
        ft_map.insert(ft_pair_type(65, "ili jopa?"));

        std_map.insert(std_pair_type(14, "meow"));
        std_map.insert(std_pair_type(17, "so smart"));
        std_map.insert(std_pair_type(15, "abc"));
        std_map.insert(std_pair_type(18, "zhopa"));
        std_map.insert(std_pair_type(65, "ili jopa?"));

        result =  compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        //hints

        ft_iterator ft_it = ft_map.insert(ft_map.begin(), ft_pair_type(2, "getting hints"));
        std_iterator std_it = std_map.insert(std_map.begin(), std_pair_type(2, "getting hints"));

        result = (std_it->first == ft_it->first) && \
                (std_it->second == ft_it->second);

        ft_it = ft_map.insert(ft_map.end(), ft_pair_type(0, "say something"));
        std_it = std_map.insert(std_map.end(), std_pair_type(0, "say something"));

        result = result && (std_it->first == ft_it->first) && \
                (std_it->second == ft_it->second);
                
        result = result && compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        //operator []

        ft_map[34] = "try me";
        ft_map[17] = "change me";
        ft_map[18] = "one more";
 
        std_map[34] = "try me";
        std_map[17] = "change me";
        std_map[18] = "one more";

        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);
        
        //insert (iterator first, iterator last);

        int vector_size = 8;

        std::vector<std_pair_type> std_vector;
	   for (unsigned int i = 0; i < vector_size; ++i)
		    std_vector.push_back(std_pair_type(vector_size - i, "came from vector"));
            
        std_map.insert(std_vector.begin(), std_vector.end());

        ft::vector<ft_pair_type> ft_vector;
	    for (unsigned int i = 0; i < vector_size; ++i)
		    ft_vector.push_back(ft_pair_type(vector_size - i, "came from vector"));

        ft_map.insert(ft_vector.begin(), ft_vector.end());

        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, true);

        file << "------------------------------------------------------------------------\n";
		file << "Erase:\n";
		std::cout << MAGENTA << "Erase:\n" << RESET;

       //erase from iterator
       
       ft_map.erase(++ft_map.begin());
        std_map.erase(++std_map.begin());

        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        ft_map.erase(ft_map.begin());
        std_map.erase(std_map.begin());

        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        ft_map.erase(--ft_map.end());
        std_map.erase(--std_map.end());

        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);


        ft_map.erase(ft_map.begin(), ++(++(++ft_map.begin())));
        std_map.erase(std_map.begin(), ++(++(++std_map.begin())));
        
        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        ft_map.erase(--(--(--ft_map.end())), --ft_map.end());
        std_map.erase(--(--(--std_map.end())), --std_map.end());
        
        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        ft_map.erase(ft_map.begin(), ft_map.end());
        std_map.erase(std_map.begin(), std_map.end());

        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, true);

        //erase from value

        std_map.insert(std_vector.begin(), std_vector.end());
        ft_map.insert(ft_vector.begin(), ft_vector.end());

        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        ft_map.erase(ft_map.begin()->first);
        std_map.erase(std_map.begin()->first);
        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        ft_map.erase((++(++(ft_map.begin())))->first);
        std_map.erase((++(++(std_map.begin())))->first);
        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        ft_map.erase((--ft_map.end())->first);
        std_map.erase((--std_map.end())->first);
        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        for (int i = 2; i < 6; ++i){
             ft_map.erase(i);
             std_map.erase(i);
        }
        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, false);

        ft_map.erase(6);
        std_map.erase(6);

        ft_map.erase(7);
        std_map.erase(7);

        result = compare_and_print_map_results(file, std_map, ft_map);
		print_result_cout(result, true);

    }
         
    file.close();

    return 0;
}
