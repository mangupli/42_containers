#include <iostream>
#include <vector>
#include "vector.hpp"


int main()
{
/*
 *---------------------------Default constructor--------------------------------
 */


	std::vector<int> vector;

	// std::cout << *(vector.begin()) << std::endl; // segfault
	//std::cout << *(vector.end()) << std::endl;  //segfault

	//std::cout << *(vector.rbegin()) << std::endl; // segfault
	//std::cout << *(vector.rend()) << std::endl;  //segfault

	std::cout << vector.size() << std::endl;
	std::cout << vector.max_size() << std::endl;
	std::cout << vector.capacity() << std::endl;
	std::cout << vector.empty() << std::endl;

	std::vector<int>::iterator it;



	std::cout << "null" << std::endl;






	ft::vector<int> myVector;
	std::cout << myVector.max_size() << std::endl;

	ft::random_access_iterator<int> myIt;





	return 0;
}
