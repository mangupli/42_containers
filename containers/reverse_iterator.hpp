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

				typedef Iterator								iterator_type;
				typedef typename Iterator::iterator_category	iterator_category;
				typedef typename Iterator::value_type			value_type;
				typedef typename Iterator::difference_type		difference_type;
				typedef typename Iterator::pointer				pointer;
				typedef typename Iterator::reference			reference;

			private:
				iterator_type base_iter;

			public:

				reverseIterator(): base_iter() {}

				/** TODO: what is this
				explicit reverseIterator (iterator_type it): base_iter(it) {}*/ 

				template <class Iter>
						reverseIterator (const reverseIterator<Iter>& rev_it): base_iter(rev_it.base()) {}

				virtual ~reverseIterator() {};

				reverseIterator & operator=(reverseIterator const & rhs )
				{
					if (this != &rhs)
						base_iter = rhs.base_iter;
					return *this;
				}


				iterator_type base() const {return base_iter;}

				reference operator*() const { return *base_iter; }

				/** TODO: what is this
				pointer operator->() const { return &(operator*()); }

				reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }*/

				reverseIterator operator+(difference_type n) const
				{
					return reverseIterator(base_iter - n);
				}

				reverseIterator& operator++()									//prefix
				{
					--base_iter;
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
					base_iter -= n;
					return *this;
				}

				reverseIterator operator-(difference_type n) const
				{
					return reverseIterator(base_iter + n);
				}

				reverseIterator& operator--()									//prefix
				{
					++base_iter;
					return *this;
				}

				reverseIterator  operator--(int)								//postfix
				{
					++base_iter;
					return *this;
				}

				reverseIterator& operator-=(difference_type n)
				{
					base_iter += n;
					return *this;
				}

			};

/*
 * --------------------Relational non-member operators -------------------------
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
