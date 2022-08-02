/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 23:28:39 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/02 15:21:17 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_TESTS_H
# define VECTOR_TESTS_H

# include "tests.hpp"


template<typename T>
void print_std_vector(const std::vector<T> & v) {
	std::cout << "print vector:\n";
	std::cout << "size: " << v.size() << " capacity: " << v.capacity() << std::endl;
	typename std::vector<T>::const_iterator it =  v.begin();
	for(int i = 0; it < v.end(); ++it, ++i){
		std::cout << "v[" << i << "] = " << *it << std::endl;
	}

}

template<typename T>
void print_ft_vector(const ft::vector<T> & v) {
	std::cout << "print vector:\n";
	std::cout << "size: " << v.size() << " capacity: " << v.capacity() << std::endl;
	typename ft::vector<T>::const_iterator it =  v.begin();
	for(int i = 0; it < v.end(); ++it, ++i){
		std::cout << "v[" << i << "] = " << *it << std::endl;
	}
}

template <class T, class Alloc>
bool	vector_comp_operators(const std::vector<T, Alloc> &stl_first, const std::vector<T, Alloc> &stl_second,
							const ft::vector<T, Alloc> &ft_first, const ft::vector<T, Alloc> &ft_second)
{
	bool result;
	result = ((stl_first < stl_second) == (ft_first < ft_second))  &&
			((stl_first <= stl_second) == (ft_first <= ft_second)) &&
			((stl_first > stl_second) == (ft_first > ft_second)) &&
			((stl_first >= stl_second) == (ft_first >= ft_second)) &&
			((stl_first == stl_second) == (ft_first == ft_second)) &&
			((stl_first != stl_second) == (ft_first != ft_second)) ;

	return result;
}

template <typename Ite_1, typename Ite_2, typename Ite_3, typename Ite_4>
bool compare_iterators(const Ite_1 &stl_first, const Ite_2 &stl_second, 
						const Ite_3 &ft_first, const Ite_4 &ft_second, const bool redo = 1)
{
	bool result;
	result = ((stl_first < stl_second) == (ft_first < ft_second))  &&
			((stl_first <= stl_second) == (ft_first <= ft_second)) &&
			((stl_first > stl_second) == (ft_first > ft_second)) &&
			((stl_first >= stl_second) == (ft_first >= ft_second)) &&
			((stl_first == stl_second) == (ft_first == ft_second)) &&
			((stl_first != stl_second) == (ft_first != ft_second)) ;


	if (redo)
		result = result && (compare_iterators(stl_second, stl_first, ft_second, ft_first, 0));
		
	return result;
}


template <class T>
bool	compare_vector_content(
	const std::vector<T>& stl_vector,
	const ft::vector<T> &ft_vector
)
{
	typename std::vector<T>::const_iterator stl_it = stl_vector.begin();
    typename ft::vector<T>::const_iterator ft_it = ft_vector.begin();

    if(ft_it != ft_vector.end() && stl_it != stl_vector.end()) {
        if (stl_vector.front() != ft_vector.front()) return false;
        if (stl_vector.back() != ft_vector.back()) return false;
    }

    while(ft_it != ft_vector.end() && stl_it != stl_vector.end())
	{
		if(*ft_it != *stl_it)
            return false;
        ++stl_it;
        ++ft_it;
	}
	return true;
}

template<class T>
void	print_vector_attributes(
	std::fstream &file,
	const std::vector<T> & stl_vector,
	const ft::vector<T> & ft_vector
)
{
	file << "------------------------------------------------------------------------\n";
	file << "STL:\n";
	file << "Empty       : " << stl_vector.empty()  << std::endl;
    file << "Size        : " << stl_vector.size() << std::endl;
    file << "Capacity    : " << stl_vector.capacity() << std::endl;
    file << "Content     : [";

    size_t count = 0;
    size_t stl_size = stl_vector.size();
	while (count < stl_size && count < 10)
    {
		file << stl_vector[count];
        if (count + 1 < stl_size)
            file << ", ";
        ++count;
    }
	if (stl_size > count)
	 	  file << "...";
    file << "]\n";

    file << std::endl;

    file << "FT : \n";
	file << "Empty       : " << ft_vector.empty()  << std::endl;
    file << "Size        : " << ft_vector.size() << std::endl;
    file << "Capacity    : " << ft_vector.capacity() << std::endl;
    file << "Content     : [";

    count = 0;
    size_t ft_size = ft_vector.size();
	while (count < ft_size && count < 10)
    {
		file << ft_vector[count];
        if (count + 1 < ft_size)
            file << ", ";
        ++count;
    }
	if (ft_size > count)
	 	  file << "...";
    file << "]\n";

	file << "------------------------------------------------------------------------\n";
}

template <class T>
bool 	compare_vector_content_and_attributes(
	const std::vector<T>& stl_vector,
	const ft::vector<T>& ft_vector){

	bool result = true;
	bool check_empty = compare_value(stl_vector.empty(), ft_vector.empty());
	bool check_size = compare_value(stl_vector.size(), ft_vector.size());
    bool check_capacity = compare_value(stl_vector.capacity(), ft_vector.capacity());
	bool check_content = compare_vector_content(stl_vector, ft_vector);
	if(check_empty == false || check_size == false || check_content == false \
                    || check_capacity == false)
		result = false;
	
	return result;
}

template <class T>
bool 	compare_and_print_vector_results(
	std::fstream &file,
	const std::vector<T>& stl_vector,
	const ft::vector<T>& ft_vector
)
{
	bool result = compare_vector_content_and_attributes(stl_vector, ft_vector);
	print_vector_attributes(file, stl_vector, ft_vector);
	print_result_file(file, result);

	return result;
}



#endif /*VECTOR_TESTS_H*/