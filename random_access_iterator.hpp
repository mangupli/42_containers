#ifndef RANDOM_ACCESS_ITERATOR_H
#define RANDOM_ACCESS_ITERATOR_H

#include "iterator_traits.hpp"
#include "utils.hpp"

namespace ft
{
	template< typename T >
	class random_access_iterator : public ft::iterator< ft::random_access_iterator_tag, T >
	{

	public:

		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::iterator_category	iterator_category;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::value_type			value_type;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::difference_type		difference_type;
		//typedef T*			pointer;
		//typedef T&			reference;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::pointer				pointer;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::reference			reference;

	private:
		pointer	_ptr;

	public:

		random_access_iterator(): _ptr(0) {}
		random_access_iterator( random_access_iterator const & other ): _ptr(other._ptr) {}
		~random_access_iterator() {}

		random_access_iterator &		operator=( random_access_iterator const & rhs );

		random_access_iterator &		operator++(); 							// версия префикс
		random_access_iterator &		operator--(); 							// версия префикс

		random_access_iterator			operator++( int ); 						// версия постфикс
		random_access_iterator			operator--( int );						// версия постфикс

		random_access_iterator &		operator+=( difference_type n );
		random_access_iterator &		operator-=( difference_type n );

		random_access_iterator &		operator[]( difference_type n );

		//random_access_iterator const &	operator[]( difference_type n ) const;  ??

		pointer		operator->();
		reference	operator*();

		//*a = t - можно присваивать
		//(void)i++ equivalent to (void)++i
		//*i++ --- return type reference

	};

/*
 * -----------------------------------------------------------------------------
 * ---------Implementation of operators of the class random_access_operator-----
 * -----------------------------------------------------------------------------
 */



/*
 * -----------------------------------------------------------------------------
 * ---------Сomparison operators for random_access_operator objects-------------
 * -----------------------------------------------------------------------------
 */

	template<typename T>
	bool operator==( random_access_iterator<T> const & lhs,
			random_access_iterator<T> const & rhs )
	{}

	template<typename T>
	bool operator!=( random_access_iterator<T> const & lhs,
			random_access_iterator<T> const & rhs )
	{}

	template<typename T>
	bool operator<( random_access_iterator<T> const & lhs,
			random_access_iterator<T> const & rhs )
	{}

	template<typename T>
	bool operator<=( random_access_iterator<T> const & lhs,
			random_access_iterator<T> const & rhs )
	{}

	template<typename T>
	bool operator>=( random_access_iterator<T> const & lhs,
			random_access_iterator<T> const & rhs )
	{}

	template<typename T>
	bool operator>( random_access_iterator<T> const & lhs,
					random_access_iterator<T> const & rhs )
	{}

/*
 * -----------------------------------------------------------------------------
 * ---------Arithmetic operators for random_access_operator objects-------------
 * -----------------------------------------------------------------------------
 */

	template<typename T>
	typename random_access_iterator<T>::difference_type
	operator-( random_access_iterator<T> const & lhs,
			random_access_iterator<T> const & rhs )
	{}

	template<typename T>
	random_access_iterator<T>
	        operator+( random_access_iterator<T> const & iterator,
			typename random_access_iterator<T>::difference_type n )
			{}


	template<typename T>
	random_access_iterator<T>
	operator+( typename random_access_iterator<T>::difference_type n,
			random_access_iterator<T> const & iterator )
			{}

	template<typename T>
	random_access_iterator<T>
	        operator-( random_access_iterator<T> const & iterator,
			typename random_access_iterator<T>::difference_type n )
			{}

	template<typename T>
	random_access_iterator<T>
	operator-( typename random_access_iterator<T>::difference_type n,
			random_access_iterator<T> const & iterator )
			{}





}






#endif