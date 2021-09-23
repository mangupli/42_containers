#ifndef RANDOM_ACCESS_ITERATOR_H
#define RANDOM_ACCESS_ITERATOR_H

#include "iterator_traits.hpp"
#include "utils.hpp"

namespace ft
{
	template< typename T >
	class random_access_iterator : ft::iterator< ft::random_access_iterator_tag, T >
	{

	public:

		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::iterator_category	iterator_category;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::value_type			value_type;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::difference_type		difference_type;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::pointer				pointer;																			pointer;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::reference			reference;																				reference;

	private:
		pointer	_ptr;

	public:

		random_access_iterator() : _ptr(0) {}


	public:





	};
}






#endif