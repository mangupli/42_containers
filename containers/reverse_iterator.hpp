#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

#include "random_access_iterator.hpp"
#include "utils.hpp"

namespace ft
{
	template< class Iterator >
	class reverseIterator
			{

			public:

				typedef Iterator												iterator_type;
				typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
				typedef typename iterator_traits<Iterator>::value_type			value_type;
				typedef typename iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename iterator_traits<Iterator>::pointer				pointer;
				typedef typename iterator_traits<Iterator>::reference			reference;

				//typedef T*			pointer;
				//typedef T&			reference;

			private:
				iterator_type _base_iter;

			public:

				reverseIterator(): _base_iter() {}
				explicit reverseIterator (iterator_type it): _base_iter(it) {}
				template <class Iter>
						reverseIterator (const reverseIterator<Iter>& rev_it): _base_iter(rev_it.base()) {}
				virtual ~reverseIterator() {};

				reverseIterator & operator=(reverseIterator const & rhs )
				{
					if (this != &rhs)
						_base_iter = rhs._base_iter;
					return *this;
				}


				iterator_type base() const {return _base_iter;}

				reference operator*() const { return *_base_iter; }
				pointer operator->() const { return &(operator*()); }
				reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

				reverseIterator operator+(difference_type n) const
				{
					return reverseIterator(_base_iter - n);
				}

				reverseIterator& operator++()									//prefix
				{
					--_base_iter;
					return *this;
				}

				reverseIterator  operator++(int)								//postfix
				{
					reverseIterator temp = *this;
					++(*this);
					return temp;
				}

				reverseIterator& operator+=(difference_type n)
				{
					_base_iter -= n;
					return *this;
				}

				reverseIterator operator-(difference_type n) const
				{
					return reverseIterator(_base_iter + n);
				}

				reverseIterator& operator--()									//prefix
				{
					++_base_iter;
					return *this;
				}

				reverseIterator  operator--(int)								//postfix
				{
					++_base_iter;
					return *this;
				}

				reverseIterator& operator-=(difference_type n)
				{
					_base_iter += n;
					return *this;
				}

			};

/*
 * -----------------------------------------------------------------------------
 * --------------------Relational non-member operators -------------------------
 * -----------------------------------------------------------------------------
 */

template <class Iterator>
		bool operator== (const reverseIterator<Iterator>& lhs,
							const reverseIterator<Iterator>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

template <class Iterator>
		bool operator!=(const reverseIterator<Iterator>& lhs,
							const reverseIterator<Iterator>& rhs)
		{
			return (lhs.base() != rhs.base());
		}

template <class Iterator>
		bool operator<(const reverseIterator<Iterator>& lhs,
							const reverseIterator<Iterator>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

template <class Iterator>
		bool operator<=(const reverseIterator<Iterator>& lhs,
							const reverseIterator<Iterator>& rhs)
		{
			return(lhs.base() >= rhs.base());
		}

template <class Iterator>
		bool operator>(const reverseIterator<Iterator>& lhs,
							 const reverseIterator<Iterator>& rhs)
		{
			return(lhs.base() < rhs.base());
		}

template <class Iterator>
		bool operator>=(const reverseIterator<Iterator>& lhs,
							const reverseIterator<Iterator>& rhs)
		{
			return(lhs.base() <= rhs.base());
		}

/*
 * -----------------------------------------------------------------------------
 * ---------------Arithmetic operators for reverse iterators-------------------
 * -----------------------------------------------------------------------------
 */

template <class Iterator>
		reverseIterator<Iterator> operator+(
					typename reverseIterator<Iterator>::difference_type n,
					const reverseIterator<Iterator>& rev_it)
		{
			return rev_it + n;
		}

template <class Iterator>
		typename reverseIterator<Iterator>::difference_type operator- (
						const reverseIterator<Iterator>& lhs,
						const reverseIterator<Iterator>& rhs)
		{
			return rhs.base() - lhs.base();
		}
}

#endif
