/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:14:46 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/09 18:14:50 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_tests.hpp"


int vector_tests()
{
	std::fstream	file;
	bool			result = true;

	mkdir("./tests/tests_output", 0777);

	std::cout << YELLOW << "---------------------------------------\n";
	std::cout << "                 VECTOR                 \n";
	std::cout << "---------------------------------------\n" << RESET;
	
	file.open("./tests/tests_output/vector_tests_output.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

	file << "VECTOR\n";

	{
		file << "------------------------------------------------------------------------\n";
		file << "Default Constructor:\n";
		std::cout << MAGENTA << "Default Constructor:\n" << RESET;


		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, false);

		ft::vector<int> const ft_vector_c;
		std::vector<int> const stl_vector_c;

		result = compare_and_print_vector_results(file, stl_vector_c, ft_vector_c);
		print_result_cout(result, true);
	}

	{
		file << "------------------------------------------------------------------------\n";
		file << "Push_back:\n";
		std::cout << MAGENTA << "Push_back:\n" << RESET;


		std::vector<std::string> stl_vector;
		ft::vector<std::string> ft_vector;

		for(int i = 0; i < 6; ++i){
			stl_vector.push_back("test");
			ft_vector.push_back("test");
		}

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, true);

		file << "------------------------------------------------------------------------\n";
		file << "Copy constructor:\n";
		std::cout << MAGENTA << "Copy constructor:\n" << RESET;


		std::vector<std::string> stl_vector_copy(stl_vector);
		ft::vector<std::string> ft_vector_copy(ft_vector);

		result = compare_and_print_vector_results(file, stl_vector_copy, ft_vector_copy);
		print_result_cout(result, false);

		ft::vector<std::string> const ft_vector_c1(ft_vector);
		std::vector<std::string> const stl_vector_c1(stl_vector);

		result = compare_and_print_vector_results(file, stl_vector_c1, ft_vector_c1);
		print_result_cout(result, true);

		file << "------------------------------------------------------------------------\n";
		file << "Pop_back:\n";
		std::cout << MAGENTA << "Pop_back:\n" << RESET;

		for(int i = 0; i < 4; ++i){
			stl_vector_copy.pop_back();
			ft_vector_copy.pop_back();
		}

		result = compare_and_print_vector_results(file, stl_vector_copy, ft_vector_copy);
		print_result_cout(result, true);


		file << "------------------------------------------------------------------------\n";
		file << "Assignment operator:\n";
		std::cout << MAGENTA << "Assignment operator:\n" << RESET;

		stl_vector_copy = stl_vector;
		ft_vector_copy = ft_vector;

		result = compare_and_print_vector_results(file, stl_vector_copy, ft_vector_copy);
		print_result_cout(result, true);

	}

	std::vector<int> v1;
	ft::vector<int> v2;

	for(int i = 0; i < 6; ++i) v1.push_back(i);
	for(int i = 0; i < 6; ++i) v2.push_back(i);

	std::vector<int> big1;
	ft::vector<int> big2;

	for(int i = 0; i < 1000; ++i) v1.push_back(i);
	for(int i = 0; i < 1000; ++i) v2.push_back(i);
	
	{

		file << "------------------------------------------------------------------------\n";
		file << "Assign:\n";
		std::cout << MAGENTA << "Assign:\n" << RESET;

		std::vector<int> stl_vector;
		ft::vector<int> ft_vector;

		file << "1: \n";

		stl_vector.assign(v1.begin(), v1.begin());
		ft_vector.assign(v2.begin(), v2.begin());

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, false);

		file << "2: \n";

		stl_vector.assign(v1.begin(), v1.end());
		ft_vector.assign(v2.begin(), v2.end());

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, false);

		file << "3: \n";

		stl_vector.assign(v1.begin(), v1.begin());
		ft_vector.assign(v2.begin(), v2.begin());

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, false);
		
		file << "4: \n";

		stl_vector.assign(big1.begin(), big1.end());
		ft_vector.assign(big2.begin(), big2.end());

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, false);

		file << "5: \n";

		stl_vector.assign(0, 123456);
		ft_vector.assign(0, 123456);

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, false);

		file << "6: \n";

		stl_vector.assign(123456, 123456);
		ft_vector.assign(123456, 123456);

		result = compare_and_print_vector_results(file, stl_vector, ft_vector);
		print_result_cout(result, true);
	}

		{
			
			file << "------------------------------------------------------------------------\n";
			file << "At:\n";
			std::cout << MAGENTA << "At:\n" << RESET;

			ft::vector<int> ft_vector(5);
			std::vector<int> stl_vector(5);
			for (size_t i = 0; i < ft_vector.size(); ++i) {
				ft_vector.at(i) = static_cast<int>((ft_vector.size() - i) * 3);
				stl_vector.at(i) =  static_cast<int>((stl_vector.size() - i) * 3);
			}

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);

			ft::vector<int> const ft_vector_c(ft_vector);
			std::vector<int> const stl_vector_c(stl_vector);
			for (size_t i = 0; i < ft_vector_c.size(); ++i) {
				result = ft_vector_c.at(i) == stl_vector_c.at(i);
				if(result == false) break;
			}

			result = result && compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, true);

		}

		{

			file << "------------------------------------------------------------------------\n";
			file << "Biderictional iterator:\n";
			std::cout << MAGENTA << "Biderictional iterator:\n" << RESET;

			std::list<int> lst;
			std::list<int>::iterator lst_it;
			for (int i = 1; i < 5; ++i)
				lst.push_back(i * 3);

			ft::vector<int> ft_vector(lst.begin(), lst.end());
			std::vector<int> stl_vector(lst.begin(), lst.end());

			result = result && compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);

		
			lst_it = lst.begin();
			for (int i = 1; lst_it != lst.end(); ++i)
				*lst_it++ = i * 5;
			ft_vector.assign(lst.begin(), lst.end());
			stl_vector.assign(lst.begin(), lst.end());

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);
	

			ft_vector.insert(ft_vector.end(), lst.rbegin(), lst.rend());
			stl_vector.insert(stl_vector.end(), lst.rbegin(), lst.rend());
			
			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, true);

			
		}

	
		{

			file << "Iterators:\n";
			std::cout << MAGENTA << "Iterators:\n" << RESET;
				
			const int size = 5;
			ft::vector<int> ft_vector(size);
			ft::vector<int>::reverse_iterator ft_it = ft_vector.rbegin();
	
			std::vector<int> stl_vector(size);
			std::vector<int>::reverse_iterator stl_it = stl_vector.rbegin();
			

			for (int i = 0; i < size; ++i){
				ft_it[i] = i * 5;
				stl_it[i] =  i * 5;
			}
				
			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);

			ft_it = ft_it + 5;
			ft_it = 1 + ft_it;
			ft_it = ft_it - 4;

			stl_it = stl_it + 5;
			stl_it = 1 + stl_it;
			stl_it = stl_it - 4;

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);

			*(ft_it -= 2) = 42;
			*(ft_it += 2) = 21;

			*(stl_it -= 2) = 42;
			*(stl_it += 2) = 21;

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);

			ft::vector<int>::const_reverse_iterator ft_ite = ft_vector.rbegin();
			std::vector<int>::const_reverse_iterator stl_ite = stl_vector.rbegin();

			result = (ft_it == ft_ite) == (stl_it == stl_ite);
			print_result_cout(result, false);

			stl_ite += 2;
			ft_ite += 2;
			result = (ft_it - ft_ite) == (stl_it - stl_ite);
			print_result_cout(result, false);

			result = compare_iterators(stl_it, stl_ite, ft_it, ft_ite);
			print_result_cout(result, true);

		}

		{
			size_t size = 5;
			
			ft::vector<foo<int> >	ft_vector(size);
			std::vector<foo<int> >	stl_vector(size);
			
			ft::vector<foo<int> >::reverse_iterator ft_it0 = ft_vector.rbegin();
			std::vector<foo<int> >::reverse_iterator stl_it0 = stl_vector.rbegin();

			ft::vector<foo<int> >::reverse_iterator ft_it1 = ft_vector.rend();
			std::vector<foo<int> >::reverse_iterator stl_it1 = stl_vector.rend();

			ft::vector<foo<int> >::const_reverse_iterator ft_cit0 = ft_vector.rbegin();
			std::vector<foo<int> >::const_reverse_iterator stl_cit0 = stl_vector.rbegin();

			ft::vector<foo<int> >::const_reverse_iterator ft_cit1 = ft_vector.rend();
			std::vector<foo<int> >::const_reverse_iterator stl_cit1 = stl_vector.rend();
			

			for (size_t i = size; ft_it0 != ft_it1; --i){
				*ft_it0++ = static_cast<int>(i);
			}

			for (size_t i = size; stl_it0 != stl_it1; --i){
				*stl_it0++ = static_cast<int>(i);
			}

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);

			result = compare_iterators(stl_it0, stl_it1, ft_it0, ft_it1);
			print_result_cout(result, false);
			

			ft_it0 = ft_vector.rbegin();
			stl_it0 = stl_vector.rbegin();

			ft::vector<foo<int> >::reverse_iterator ft_it_mid;
			std::vector<foo<int> >::reverse_iterator stl_it_mid;

			ft::vector<foo<int> >::const_reverse_iterator ft_cit_mid;
			std::vector<foo<int> >::const_reverse_iterator stl_cit_mid;

			ft_it_mid = ft_it0 + 3;
			stl_it_mid = stl_it0 + 3;

			ft_cit_mid = ft_it0 + 3;
			stl_cit_mid = stl_it0 + 3;
			
			ft_cit_mid = ft_cit0 + 3;
			stl_cit_mid = stl_cit0 + 3;

			ft_cit_mid = ft_it_mid;
			stl_cit_mid = stl_it_mid;


			result = ((ft_it0 + 3 == ft_cit0 + 3) && (ft_cit0 + 3 == ft_it_mid)) &&
					((stl_it0 + 3 == stl_cit0 + 3) && (stl_cit0 + 3 == stl_it_mid));

			print_result_cout(result, false);

			result = compare_iterators(stl_it0 + 3, stl_it_mid, ft_it0 + 3, ft_it_mid);
			print_result_cout(result, false);

			result = compare_iterators(stl_it0, stl_it1, ft_it0, ft_it1);
			print_result_cout(result, false);

			result = compare_iterators(stl_it1-3, stl_it_mid, ft_it1-3, ft_it_mid);
			print_result_cout(result, true);

			result = compare_iterators(stl_cit0 + 3, stl_cit_mid, ft_cit0 + 3, ft_cit_mid);
			print_result_cout(result, false);

			result = compare_iterators(stl_cit0, stl_cit1, ft_cit0, ft_cit1);
			print_result_cout(result, false);

			result = compare_iterators(stl_cit1-3, stl_cit_mid, ft_cit1-3, ft_cit_mid);
			print_result_cout(result, false);

			result = compare_iterators(stl_it0, stl_cit1, ft_it0, ft_cit1);
			print_result_cout(result, false);

			result = compare_iterators(stl_it_mid, stl_cit1-3, ft_it_mid, ft_cit1-3);
			print_result_cout(result, false);

			result = compare_iterators(stl_it1, stl_cit0, ft_it1, ft_cit0);
			print_result_cout(result, true);			

		}
				{
			file << "------------------------------------------------------------------------\n";
			file << "Erase:\n";
			std::cout << MAGENTA << "Erase:\n" << RESET;
				
			ft::vector<std::string> ft_vector(10);
			std::vector<std::string> stl_vector(10);

			for (unsigned long int i = 0; i < ft_vector.size(); ++i){
				ft_vector[i] = std::string((ft_vector.size() - i), i + 65);
				stl_vector[i] = std::string((stl_vector.size() - i), i + 65);
			}

		
			ft_vector.erase(ft_vector.begin() + 2);
			stl_vector.erase(stl_vector.begin() + 2);

				file << "1: \n";

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);

			ft_vector.erase(ft_vector.begin());
			stl_vector.erase(stl_vector.begin());

				file << "2: \n";

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);

			ft_vector.erase(ft_vector.end()-1);
			stl_vector.erase(stl_vector.end()-1);

				file << "3: \n";

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);

			ft_vector.erase(ft_vector.begin(), ft_vector.begin() + 3);
			stl_vector.erase(stl_vector.begin(), stl_vector.begin() + 3);

				file << "4: \n";

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);

			ft_vector.erase(ft_vector.end() - 3, ft_vector.end() - 1);
			stl_vector.erase(stl_vector.end() - 3, stl_vector.end() - 1);

				file << "5: \n";

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);

			ft_vector.push_back("Hello");
			stl_vector.push_back("Hello");

			ft_vector.push_back("Hi there");
			stl_vector.push_back("Hi there");

			ft_vector.erase(ft_vector.end() - 3, ft_vector.end());
			stl_vector.erase(stl_vector.end() - 3, stl_vector.end());

				file << "6: \n";

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);

			ft_vector.push_back("ONE");
			stl_vector.push_back("ONE");

			ft_vector.push_back("TWO");
			stl_vector.push_back("TWO");

			ft_vector.push_back("THREE");
			stl_vector.push_back("THREE");

			ft_vector.erase(ft_vector.begin(), ft_vector.end());
			stl_vector.erase(stl_vector.begin(), stl_vector.end());

				file << "7: \n";

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, true);

		}

		{
			file << "Insert:\n";
			std::cout << MAGENTA << "Insert:\n" << RESET;
				
			ft::vector<int> ft_vector(10);
			std::vector<int> stl_vector(10);

			ft::vector<int> ft_vector2;
			std::vector<int> stl_vector2;



			for(size_t i = 0; i < ft_vector.size(); ++i){
				ft_vector[i] = static_cast<int>((ft_vector.size() - i) * 3);
				stl_vector[i] = static_cast<int>((stl_vector.size() - i) * 3);
			}
		


			ft_vector2.insert(ft_vector2.end(), 42);
			stl_vector2.insert(stl_vector2.end(), 42);

				file << "1: \n";

			result = compare_and_print_vector_results(file, stl_vector2, ft_vector2);
			print_result_cout(result, false);

			ft_vector2.insert(ft_vector2.begin(), 2, 21);
			stl_vector2.insert(stl_vector2.begin(), 2, 21);

				file << "2: \n";

			result = compare_and_print_vector_results(file, stl_vector2, ft_vector2);
			print_result_cout(result, false);

			ft_vector2.insert(ft_vector2.end() - 2, 42);
			stl_vector2.insert(stl_vector2.end() - 2, 42);

				file << "3: \n";

			result = compare_and_print_vector_results(file, stl_vector2, ft_vector2);
			print_result_cout(result, false);

			ft_vector2.insert(ft_vector2.end(), 2, 84);
			stl_vector2.insert(stl_vector2.end(), 2, 84);

				file << "4: \n";

			result = compare_and_print_vector_results(file, stl_vector2, ft_vector2);
			print_result_cout(result, false);

			ft_vector2.resize(4);
			stl_vector2.resize(4);

			ft_vector2.insert(ft_vector2.begin() + 2, ft_vector.begin(), ft_vector.end());
			stl_vector2.insert(stl_vector2.begin() + 2, stl_vector.begin(), stl_vector.end());

			file << "5: \n";

			result = compare_and_print_vector_results(file, stl_vector2, ft_vector2);
			print_result_cout(result, false);

			ft_vector.clear();
			stl_vector.clear();

			file << "6: \n";

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, false);

			ft::vector<int> ft_vector3;
			std::vector<int> stl_vector3;

			for (int i = 0; i < 5; ++i){
				ft_vector3.insert(ft_vector3.end(), i);
				stl_vector3.insert(stl_vector3.end(), i);
			}

			ft_vector3.insert(ft_vector3.begin() + 1, 2, 111);
			stl_vector3.insert(stl_vector3.begin() + 1, 2, 111);

			file << "7: \n";

			result = compare_and_print_vector_results(file, stl_vector, ft_vector);
			print_result_cout(result, true);
				

		}
		{
			file << "Swap:\n";
			std::cout << MAGENTA << "Swap:\n" << RESET;


			ft::vector<int> ft_foo(3, 15);
			ft::vector<int> ft_bar(5, 42);

			std::vector<int> stl_foo(3, 15);
			std::vector<int> stl_bar(5, 42);

			ft::vector<int>::const_iterator ft_it_foo = ft_foo.begin();
			ft::vector<int>::const_iterator ft_it_bar = ft_bar.begin();
			
			std::vector<int>::const_iterator stl_it_foo = stl_foo.begin();
			std::vector<int>::const_iterator stl_it_bar = stl_bar.begin();

			ft_foo.swap(ft_bar);
			stl_foo.swap(stl_bar);

			result = compare_and_print_vector_results(file, stl_foo, ft_foo);
			print_result_cout(result, false);
			
			result = compare_and_print_vector_results(file, stl_bar, ft_bar);
			print_result_cout(result, false);

			result = (ft_it_foo == ft_bar.begin()) == (stl_it_foo == stl_bar.begin());
			print_result_cout(result, false);

			result = (ft_it_bar == ft_foo.begin()) == (stl_it_bar == stl_foo.begin());
			print_result_cout(result, true);
		}

		{
			file << "Relational operators:\n";
			std::cout << MAGENTA << "Relational operators:\n" << RESET;

			ft::vector<int> ft_vector(4);
			ft::vector<int> ft_vector2(4);

			std::vector<int> stl_vector(4);
			std::vector<int> stl_vector2(4);

			result = vector_comp_operators(stl_vector, stl_vector, ft_vector, ft_vector);
			print_result_cout(result, false);

			result = vector_comp_operators(stl_vector, stl_vector2, ft_vector, ft_vector2);
			print_result_cout(result, false);

			ft_vector2.resize(10);
			stl_vector2.resize(10);
			
			result = vector_comp_operators(stl_vector, stl_vector2, ft_vector, ft_vector2);
			print_result_cout(result, false);

			result = vector_comp_operators(stl_vector2, stl_vector, ft_vector2, ft_vector);
			print_result_cout(result, false);

			ft_vector[2] = 42;
			stl_vector[2] = 42;

			result = vector_comp_operators(stl_vector, stl_vector2, ft_vector, ft_vector2);
			print_result_cout(result, false);

			ft::swap(ft_vector2, ft_vector);
			ft::swap(stl_vector2, stl_vector);

			result = vector_comp_operators(stl_vector, stl_vector2, ft_vector, ft_vector2);
			print_result_cout(result, true);
			
		}
		

		
			
	

	file.close();

	return 0;
}
