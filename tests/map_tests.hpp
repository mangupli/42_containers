/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:54:49 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/10 15:05:58 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_TESTS_H
# define MAP_TESTS_H

# include "tests.hpp"

template <typename T>
std::string	print_pair(std::fstream &file, const T &iterator)
{
	file << "key: " << iterator->first << " | value: " << iterator->second << std::endl;
	return ("");
}

template <class Key, class T>
bool	compare_map_content(
	const std::map<Key, T>& stl_map,
	const ft::map<Key, T> &ft_map
)
{
	typename std::map<Key, T>::const_iterator stl_it = stl_map.begin();
    typename ft::map<Key, T>::const_iterator ft_it = ft_map.begin();

    while(ft_it != ft_map.end() && stl_it != stl_map.end())
	{
		if( stl_it->first != ft_it->first || stl_it->second != ft_it->second)
            return false;
        ++stl_it;
        ++ft_it;
	}
	return true;
}

template<class Key, class T >
void	print_map_attributes(
	std::fstream &file,
	const std::map<Key, T> & stl_map,
	const ft::map<Key, T> & ft_map
)
{
	file << "------------------------------------------------------------------------\n";
	file << "STL:\n";
	file << "Empty       : " << stl_map.empty()  << std::endl;
    file << "Size        : " << stl_map.size() << std::endl;
    file << "Content     : \n";

    size_t count = 0;
    typename std::map<Key, T>::const_iterator stl_ite = stl_map.begin();
    for( ; stl_ite != stl_map.end() && count < 10; ++stl_ite, ++count){
        print_pair(file, stl_ite);
    }
	if (stl_map.size() > count)
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
	const std::map<Key, T>& stl_map,
	const ft::map<Key, T>& ft_map){

	bool result = true;
	bool check_empty = compare_value(stl_map.empty(), ft_map.empty());
	bool check_size = compare_value(stl_map.size(), ft_map.size());
	bool check_content = compare_map_content(stl_map, ft_map);
	if(check_empty == false || check_size == false || check_content == false)
		result = false;
	
	return result;
}

template <class Key, class T>
bool 	compare_and_print_map_results(
	std::fstream &file,
	const std::map<Key, T>& stl_map,
	const ft::map<Key, T>& ft_map
)
{
	bool result = compare_map_content_and_attributes(stl_map, ft_map);
	print_map_attributes(file, stl_map, ft_map);
	print_result_file(file, result);

	return result;
}



#endif /*MAP_TESTS_H*/