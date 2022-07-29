#ifndef RANDOM_ACCESS_ITERATOR_H
#define RANDOM_ACCESS_ITERATOR_H


#include "utils.hpp"
#include "iterator.hpp"

namespace ft
{
	template< typename T >
	class random_access_iterator : public ft::iterator< ft::random_access_iterator_tag, T >
	{
		typedef typename ft::random_access_iterator<T>											self;

	public:

		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::iterator_category	iterator_category;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::value_type			value_type;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::difference_type		difference_type;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::pointer				pointer;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::reference			reference;

	private:
		pointer	_ptr;

	public:

		random_access_iterator(): _ptr(0) {}
		random_access_iterator(pointer ptr): _ptr(ptr) {}
		random_access_iterator( random_access_iterator const & other ): _ptr(other._ptr) {}
		~random_access_iterator() {}

		pointer base() const { 
			return _ptr;
		}

		self & operator=( random_access_iterator const & rhs )
		{
			if (this != &rhs)
				_ptr = rhs._ptr;
			return *this;
		}

		reference operator[]( difference_type n ) const {
			return *(*this + n);
		}

		pointer operator->() const {
			return _ptr;
		}
		reference operator*() const {
			return *_ptr;
		}

		self & operator+=( difference_type n )
		{
			this->_ptr += n;
			return *this;
		}

		self & operator-=( difference_type n ) {
			this->_ptr -= n;
			return *this;
		}

		self & operator++() { 							// prefix
			++_ptr;
			return *this;
		}

		self & operator--() { 							// prefix
		
			--_ptr;
			return *this;
		}

		self operator++( int ) { 						// postfix
			self tmp(*this);
			++_ptr;
			return tmp;
		}

		self operator--( int ) {						// postfix
			self tmp(*this);
			--_ptr;
			return tmp;
		}

		self operator+( difference_type n ) const {
			self tmp(*this);
			return tmp += n;
		}

		self operator-( difference_type n ) const {
			self tmp(*this);
			return tmp -= n;
		}

		/** TODO:
		//*a = t - можно присваивать
		//(void)i++ equivalent to (void)++i
		//*i++ --- return type reference
		*/

	}; /*class random_access_iterator*/

	template<class T>
	typename random_access_iterator<T>::difference_type
		operator-( random_access_iterator<T> const & lhs,
					random_access_iterator<T> const & rhs ) {
		return lhs.base() - rhs.base();
	}

	template<class T>
	random_access_iterator<T> operator+( typename random_access_iterator<T>::difference_type n,
					random_access_iterator<T> const & rhs ) {
		return rhs += n;
	}

	template<class T>
	inline bool operator==( random_access_iterator<T> const & lhs,
								random_access_iterator<T> const & rhs) {
		return lhs.base() == rhs.base();
	}

	template<class T>
	inline bool operator!=( random_access_iterator<T> const & lhs,
								random_access_iterator<T> const & rhs) {
		return lhs.base() != rhs.base();
	}

	template<class T>
	inline bool operator<( random_access_iterator<T> const & lhs,
								random_access_iterator<T> const & rhs ) {
		return lhs.base() < rhs.base();
	}

	template<class T>
	inline bool operator<=( random_access_iterator<T> const & lhs,
								random_access_iterator<T> const & rhs ) {
		return lhs.base() <= rhs.base();
	}

	template<class T>
	inline bool operator>( random_access_iterator<T> const & lhs,
								random_access_iterator<T> const & rhs ) {
		return lhs.base() > rhs.base();
	}

	template<class T>
	inline bool operator>=( random_access_iterator<T> const & lhs,
								random_access_iterator<T> const & rhs ) {
		return lhs.base() >= rhs.base();
	}

} /*namespace ft*/

#endif /*ITERATOR_H*/