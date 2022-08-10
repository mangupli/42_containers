/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:54:49 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/10 16:49:45 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TESTS_H
# define MAP_TESTS_H

# include "tests.hpp"

template <class Key, class T>
bool	map_comp_operators(const std::map<Key, T> &std_first, const std::map<Key, T> &std_second,
							const ft::map<Key, T> &ft_first, const ft::map<Key, T> &ft_second)
{
	bool result;
	result = ((std_first < std_second) == (ft_first < ft_second))  &&
			((std_first <= std_second) == (ft_first <= ft_second)) &&
			((std_first > std_second) == (ft_first > ft_second)) &&
			((std_first >= std_second) == (ft_first >= ft_second)) &&
			((std_first == std_second) == (ft_first == ft_second)) &&
			((std_first != std_second) == (ft_first != ft_second)) ;

	return result;
}



template <typename T>
std::string	print_pair(std::fstream &file, const T &iterator)
{
	file << "key: " << iterator->first << " | value: " << iterator->second << std::endl;
	return ("");
}

template <class Key, class T>
bool	compare_map_content(
	const std::map<Key, T>& std_map,
	const ft::map<Key, T> &ft_map
)
{
	typename std::map<Key, T>::const_iterator std_it = std_map.begin();
    typename ft::map<Key, T>::const_iterator ft_it = ft_map.begin();

    while(ft_it != ft_map.end() && std_it != std_map.end())
	{
		if( std_it->first != ft_it->first || std_it->second != ft_it->second)
            return false;
        ++std_it;
        ++ft_it;
	}
	return true;
}

template<class Key, class T >
void	print_map_attributes(
	std::fstream &file,
	const std::map<Key, T> & std_map,
	const ft::map<Key, T> & ft_map
)
{
	file << "------------------------------------------------------------------------\n";
	file << "STL:\n";
	file << "Empty       : " << std_map.empty()  << std::endl;
    file << "Size        : " << std_map.size() << std::endl;
    file << "Content     : \n";

    size_t count = 0;
    typename std::map<Key, T>::const_iterator std_ite = std_map.begin();
    for( ; std_ite != std_map.end() && count < 10; ++std_ite, ++count){
        print_pair(file, std_ite);
    }
	if (std_map.size() > count)
	 	  file << "...";
    file << std::endl;

    file << "FT : \n";
	file << "Empty       : " << ft_map.empty()  << std::endl;
    file << "Size        : " << ft_map.size() << std::endl;
    file << "Content     : \n";

    count = 0;
    typename ft::map<Key, T>::const_iterator ft_ite = ft_map.begin();
    for( ; ft_ite != ft_map.end() && count < 10; ++ft_ite, ++count){
        print_pair(file, ft_ite);
    }
	if (ft_map.size() > count)
	 	  file << "...";
    file << std::endl;

	file << "------------------------------------------------------------------------\n";
}

template <class Key, class T>
bool 	compare_map_content_and_attributes(
	const std::map<Key, T>& std_map,
	const ft::map<Key, T>& ft_map){

	bool result = true;
	bool check_empty = compare_value(std_map.empty(), ft_map.empty());
	bool check_size = compare_value(std_map.size(), ft_map.size());
	bool check_content = compare_map_content(std_map, ft_map);
	if(check_empty == false || check_size == false || check_content == false)
		result = false;
	
	return result;
}

template <class Key, class T>
bool 	compare_and_print_map_results(
	std::fstream &file,
	const std::map<Key, T>& std_map,
	const ft::map<Key, T>& ft_map
)
{
	bool result = compare_map_content_and_attributes(std_map, ft_map);
	print_map_attributes(file, std_map, ft_map);
	print_result_file(file, result);

	return result;
}



#endif /*MAP_TESTS_H*/