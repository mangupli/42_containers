#ifndef RANDOM_ACCESS_ITERATOR_H
#define RANDOM_ACCESS_ITERATOR_H

#include "iterator_traits.hpp"
#include "utils.hpp"
#include "iterator.hpp"

namespace ft
{
	template< typename T >
	class random_access_iterator : public ft::iterator< ft::random_access_iterator_tag, T >
	{

	public:

		// TODO: затайпдефить длинные названия random_access_iterator и референсы на него
		// TODO: как можно заинхеритеть от бидирекшионала, чтобы возвращался нужный тип

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

		random_access_iterator & operator=( random_access_iterator const & rhs )
		{
			if (this != &rhs)
				_ptr = rhs._ptr;
			return *this;
		}

		random_access_iterator & operator++() 							// prefix
		{
			++_ptr;
			return *this;
		}

		random_access_iterator & operator--() 							// prefix
		{
			--_ptr;
			return *this;
		}

		random_access_iterator operator++( int ) 						// postfix
		{
			random_access_iterator<T> tmp(*this);
			++tmp;
			//~*this;
			return tmp;
		}

		random_access_iterator operator--( int )						// postfix
		{
			random_access_iterator<T> tmp(*this);
			--(tmp);
			//~*this;
			return tmp;
		}

		random_access_iterator operator+( difference_type n )
		{
			random_access_iterator<T> tmp(this->_ptr + n);
			//~*this;
			return tmp;
		}

		random_access_iterator operator-( difference_type n )
		{
			random_access_iterator<T> tmp(this->_ptr - n);
			//~*this;
			return tmp;
		}

		random_access_iterator & operator+=( difference_type n )
		{
			this->_ptr += n;
			return *this;
		}

		random_access_iterator & operator-=( difference_type n )
		{
			this->_ptr -= n;
			return *this;
		}

		random_access_iterator & operator[]( difference_type n )
		{
			return *(*this + n);
		}

		//random_access_iterator const &	operator[]( difference_type n ) const;  ??

		pointer operator->()
		{
			return this->_ptr;
		}
		reference operator*()
		{
			return *(this->_ptr);
		}

		//*a = t - можно присваивать
		//(void)i++ equivalent to (void)++i
		//*i++ --- return type reference

		bool operator==( random_access_iterator<T> const & rhs) { return this->_ptr == rhs.ptr; }
		bool operator!=( random_access_iterator<T> const & rhs) { return this->_ptr != rhs.ptr; }
		bool operator<( random_access_iterator<T> const & rhs) { return this->_ptr < rhs.ptr; }
		bool operator<=( random_access_iterator<T> const & rhs) { return this->_ptr <= rhs.ptr; }
		bool operator>( random_access_iterator<T> const & rhs) { return this->_ptr > rhs.ptr; }
		bool operator>=( random_access_iterator<T> const & rhs) { return this->_ptr >= rhs.ptr; }


		friend difference_type operator-( ft::random_access_iterator<T> const & lhs,
				ft::random_access_iterator<T> const & rhs)
		{
			return (lhs._ptr - rhs._ptr);
		}

		friend random_access_iterator operator+(difference_type n,
										random_access_iterator<T> const & iterator)
		{
			return iterator + n;
		}
	};
}

#endif