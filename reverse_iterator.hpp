#ifndef REVERSE_RAI_ITERATOR_H
#define REVERSE_RAI_ITERATOR_H

#include "random_access_iterator.hpp"
#include "utils.hpp"

namespace ft
{
	template< class Iterator >
	class reverse_iterator
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

				reverse_iterator(): _base_iter() {}
				explicit reverse_iterator (iterator_type it): _base_iter(it) {}
				template <class Iter>
						reverse_iterator (const reverse_iterator<Iter>& rev_it): _base_iter(rev_it.base()) {}
				virtual ~reverse_iterator() {};

				reverse_iterator & operator=( reverse_iterator const & rhs )
				{
					if (this != &rhs)
						_base_iter = rhs._base_iter;
					return *this;
				}


				iterator_type base() const {return _base_iter;}

				reference operator*() const { return *_base_iter; }
				pointer operator->() const { return &(operator*()); }
				reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

				reverse_iterator operator+(difference_type n) const
				{
					return reverse_iterator(_base_iter - n);
				}

				reverse_iterator& operator++()									//prefix
				{
					--_base_iter;
					return *this;
				}

				reverse_iterator  operator++(int)								//postfix
				{
					reverse_iterator temp = *this;
					++(*this);
					return temp;
				}

				reverse_iterator& operator+=(difference_type n)
				{
					_base_iter -= n;
					return *this;
				}

				reverse_iterator operator-(difference_type n) const
				{
					return reverse_iterator(_base_iter + n);
				}

				reverse_iterator& operator--()									//prefix
				{
					++_base_iter;
					return *this;
				}

				reverse_iterator  operator--(int)								//postfix
				{
					++_base_iter;
					return *this;
				}

				reverse_iterator& operator-=(difference_type n)
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
		bool operator== (const reverse_iterator<Iterator>& lhs,
							const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() == rhs.base());
		}

template <class Iterator>
		bool operator!=(const reverse_iterator<Iterator>& lhs,
							const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() != rhs.base());
		}

template <class Iterator>
		bool operator<(const reverse_iterator<Iterator>& lhs,
							const reverse_iterator<Iterator>& rhs)
		{
			return (lhs.base() > rhs.base());
		}

template <class Iterator>
		bool operator<=(const reverse_iterator<Iterator>& lhs,
							const reverse_iterator<Iterator>& rhs)
		{
			return(lhs.base() >= rhs.base());
		}

template <class Iterator>
		bool operator>(const reverse_iterator<Iterator>& lhs,
							 const reverse_iterator<Iterator>& rhs)
		{
			return(lhs.base() < rhs.base());
		}

template <class Iterator>
		bool operator>=(const reverse_iterator<Iterator>& lhs,
							const reverse_iterator<Iterator>& rhs)
		{
			return(lhs.base() <= rhs.base());
		}

/*
 * -----------------------------------------------------------------------------
 * ---------------Arithmetic operators for reverse iterators-------------------
 * -----------------------------------------------------------------------------
 */

template <class Iterator>
		reverse_iterator<Iterator> operator+(
					typename reverse_iterator<Iterator>::difference_type n,
					const reverse_iterator<Iterator>& rev_it)
		{
			return rev_it + n;
		}

template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator- (
						const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs)
		{
			return rhs.base() - lhs.base();
		}
}

#endif
