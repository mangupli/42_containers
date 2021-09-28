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
		random_access_iterator(pointer ptr): _ptr(ptr) {}
		random_access_iterator( random_access_iterator const & other ): _ptr(other._ptr) {}
		~random_access_iterator() {}

		random_access_iterator &		operator=( random_access_iterator const & rhs );

		random_access_iterator &		operator++(); 							// версия префикс
		random_access_iterator &		operator--(); 							// версия префикс

		random_access_iterator			operator++( int ); 						// версия постфикс
		random_access_iterator			operator--( int );						// версия постфикс

		random_access_iterator			operator+( difference_type n );
		random_access_iterator			operator-( difference_type n );

		random_access_iterator &		operator+=( difference_type n );
		random_access_iterator &		operator-=( difference_type n );

		random_access_iterator &		operator[]( difference_type n );

		//random_access_iterator const &	operator[]( difference_type n ) const;  ??

		pointer		operator->();
		reference	operator*();

		//*a = t - можно присваивать
		//(void)i++ equivalent to (void)++i
		//*i++ --- return type reference

		friend bool operator==( random_access_iterator<T> const &,
				random_access_iterator<T> const & );

		friend bool operator<( random_access_iterator<T> const &,
				random_access_iterator<T> const & );

		friend bool operator-( random_access_iterator<T> const &,
				random_access_iterator<T> const & );

	};

/*
 * -----------------------------------------------------------------------------
 * ---------Implementation of operators of the class random_access_operator-----
 * -----------------------------------------------------------------------------
 */

	template< typename T >
	random_access_iterator<T> & random_access_iterator<T>::operator=
			( random_access_iterator const & rhs )
	{
		if (this != &rhs)
			_ptr = rhs._ptr;
		return *this;
	}

	template< typename T >
	random_access_iterator<T> & random_access_iterator<T>::operator++()
	{
		++_ptr;
		return *this;
	}

	template< typename T >
	random_access_iterator<T> & random_access_iterator<T>::operator--()
	{
		--_ptr;
		return *this;
	}

	template< typename T >
	random_access_iterator<T> random_access_iterator<T>::operator++( int )
	{
		random_access_iterator<T> tmp(*this);
		++(*this);
		return tmp;
	}

	template< typename T >
	random_access_iterator<T> random_access_iterator<T>::operator--( int )
	{
		random_access_iterator<T> tmp(*this);
		--(*this);
		return tmp;
	}

	template< typename T >
	random_access_iterator<T>
	random_access_iterator<T>::operator+( difference_type n )
	{
		random_access_iterator<T> tmp(this->ptr + n);
		return tmp;
	}

	template< typename T >
	random_access_iterator<T>
	random_access_iterator<T>::operator-( difference_type n )
	{
		random_access_iterator<T> tmp(this->ptr - n);
		return tmp;
	}

	template< typename T >
	random_access_iterator<T> &
	random_access_iterator<T>::operator+=( difference_type n )
	{
		this->_prt += n;
		return *this;
	}

	template< typename T >
	random_access_iterator<T> &
	random_access_iterator<T>::operator-=( difference_type n )
	{
		this->_prt -= n;
		return *this;
	}

	template< typename T >
	random_access_iterator<T> &
	random_access_iterator<T>::operator[]( difference_type n )
	{
		return *(*this + n);
	}

	template< typename T >
	typename random_access_iterator<T>::pointer
	random_access_iterator<T>::operator->()
	{
		return this->_ptr;
	}

	template< typename T >
	typename random_access_iterator<T>::reference
	random_access_iterator<T>::operator*()
	{
		return *(this->_ptr);
	}


/*
 * -----------------------------------------------------------------------------
 * ---------Сomparison operators for random_access_operator objects-------------
 * -----------------------------------------------------------------------------
 */

	template< typename T >
	bool operator==( random_access_iterator<T> const & lhs,
			random_access_iterator<T> const & rhs )
	{
		return (lhs._ptr == rhs._ptr);
	}

	template< typename T >
	bool operator!=( random_access_iterator<T> const & lhs,
			random_access_iterator<T> const & rhs )
	{
		return !(lhs._ptr == rhs._ptr);
	}

	template< typename T >
	bool operator<( random_access_iterator<T> const & lhs,
			random_access_iterator<T> const & rhs )
	{
		return (lhs._ptr < rhs._ptr);
	}

	template< typename T >
	bool operator>( random_access_iterator<T> const & lhs,
					random_access_iterator<T> const & rhs )
	{
		return (rhs < lhs);
	}

	template< typename T >
	bool operator<=( random_access_iterator<T> const & lhs,
			random_access_iterator<T> const & rhs )
	{
		return !(rhs < lhs);
	}

	template< typename T >
	bool operator>=( random_access_iterator<T> const & lhs,
			random_access_iterator<T> const & rhs )
	{
		return !(lhs < rhs);
	}


/*
 * -----------------------------------------------------------------------------
 * ---------Arithmetic operators for random_access_operator objects-------------
 * -----------------------------------------------------------------------------
 */

	template< typename T >
	typename random_access_iterator<T>::difference_type
	operator-( random_access_iterator<T> const & lhs,
			random_access_iterator<T> const & rhs )
	{
		return (lhs._ptr - rhs._ptr);
	}

	template< typename T >
	random_access_iterator<T>
	operator+( typename random_access_iterator<T>::difference_type n,
									random_access_iterator<T> const & iterator )
	{
		return iterator + n;
	}

	template< typename T >
	random_access_iterator<T>
	operator-( typename random_access_iterator<T>::difference_type n,
			random_access_iterator<T> const & iterator )
	{
		return iterator - n;
	}
}


#endif