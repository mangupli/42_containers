#include <iostream>
#include <vector>

#include "../containers/random_access_iterator.hpp"
#include "../containers/vector.hpp"


int vector_tests()
{
/*
 *---------------------------Default constructor--------------------------------
 */

/*

int n = 10;
	std::vector<int> vector(n);
	for(int i = 0; i < n; ++i)
		vector[i] = i;

	std::cout << "size of std::vector<int> vector(10): " << vector.size() << std::endl;
	std::cout << "capacity: " << vector.capacity() << std::endl;
	for(int i = 0; i < n + 1; ++i)
		std::cout << "vector [" << i << "]: " << vector[i] << std::endl;

	std::vector<int>::iterator first = vector.begin();
	std::vector<int>::iterator last = vector.begin() + 5;

	std::cout << "vector.begin() + 5: " << *last << std::endl;

	{
		std::cout << "----------------------------------------" << std::endl;

		std::vector<int> vector(first, last);

		std::cout << "std::distance: " << std::distance(first, last) << std::endl;
		std::cout << "ft::distance: " << ft::distance(first, last) << std::endl;
		std::cout << "size: " << vector.size() << std::endl;
		std::cout << "capacity: " << vector.capacity() << std::endl;

		for(int i = 0; i < vector.size() ; ++i)
			vector[i] = i;
		for(int i = 0; i < vector.size() ; ++i)
			std::cout << "vector [" << i << "]: " << vector[i] << std::endl;
	}

	// std::cout << *(vector.begin()) << std::endl; // segfault
	//std::cout << *(vector.end()) << std::endl;  // segfault

	//std::cout << *(vector.rbegin()) << std::endl; // segfault
	//std::cout << *(vector.rend()) << std::endl;  //segfault






	std::vector<int> newVector(vector.begin(), vector.end());

	std::vector<int>::iterator itBegin( vector.begin() );

	//std::cout << "itBegin[10] " << itBegin[112] << std::endl;

 */


	/*

	std::vector<std::string> vstring;
	std::cout << "default capacity: " << vstring.capacity() << std::endl;
	std::cout << "default size: " << vstring.size() << std::endl;

	for (int i = 0; i < 10; ++i)
	{
		std::vector<std::string> vstring(i);
		std::cout << i << " capacity: " << vstring.capacity() << std::endl;
		std::cout << i << " size: " << vstring.size() << std::endl;
	}

	*/



	ft::vector<int> myVector(10, 42);


	std::cout << "ft::size:	" << myVector.size() << std::endl;
	std::cout << "ft::capacity:	" << myVector.capacity() << std::endl;

	std::cout << "ft::vector[0]:	" << myVector[0] << std::endl;

	myVector[0] = 21;

	std::cout << "ft::vector[0]:	" << myVector[0] << std::endl;
	std::cout << "*ft::vector.begin():	" << *myVector.begin() << std::endl;


	for (int i = 0; i < 10; ++i)
		myVector[i] = i;

	/*
		for (int i = 0; i < 10; ++i)
			std::cout << "ft::vector[" << i << "]:	" << myVector[i] << std::endl;
	*/

	ft::vector<int>::iterator itBegin = myVector.begin();
	ft::vector<int>::iterator itEnd = myVector.end();

	std::cout << "*itBegin:	" << *itBegin << std::endl;
	std::cout << "*itEnd:	" << *(itEnd - 1) << std::endl;

	std::cout << "itEnd - itBegin -- " << itEnd - itBegin << std::endl;

	int counter = 3;
	for ( ; itBegin < itEnd; ++itBegin)
	{
		*itBegin = counter * 3;
		++counter;
	}

	itBegin = myVector.begin();

	for ( ; itBegin < itEnd; ++itBegin)
		std::cout << "*itBegin:	" << *itBegin << std::endl;


	std::vector<int> stdVector(10, 5);


	return 0;
}
