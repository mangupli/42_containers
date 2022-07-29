/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 14:38:45 by mspyke            #+#    #+#             */
/*   Updated: 2022/07/29 12:06:22 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_H
#define ITERATOR_H

# include <cstddef>

namespace ft
{
	/**
	 * @brief This implemenation of iterator_traits was taken from the standard 98, 
	 * with 5 type aliases, personally I think it is mostly meaningless.
	 * For better help it should check the validation of all this type in the class Iterator
	 * using SFINAE and some type_traits
	 * 
	 * @tparam Iterator the type of an iterator
	 */
	
	template<class Iterator> struct iterator_traits {
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	template<class T> struct iterator_traits<T*> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};
	
	template<class T> struct iterator_traits<const T*> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template< class Category, class T, class Distance = std::ptrdiff_t,
					class Pointer = T*, class Reference = T& >
	struct iterator {
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef T const *	const_pointer;
		typedef Reference	reference;
		typedef T const &	const_reference;
	};


	template <class InputIterator, class Distance>
		void advance(InputIterator& i, Distance n);
	
	template <class InputIterator>
		typename iterator_traits<InputIterator>::difference_type
				distance(InputIterator first, InputIterator last);

namespace detail {
	
	template<class InputIterator>
		typename ft::iterator_traits<InputIterator>::difference_type 
		do_distance(InputIterator first, InputIterator last, ft::input_iterator_tag) {
   			typename ft::iterator_traits<InputIterator>::difference_type result = 0;
    		while (first != last) {
        		++first;
        		++result;
    		}
    	return result;
	}
 
	template<class InputIterator>
		typename ft::iterator_traits<InputIterator>::difference_type 
   		do_distance(InputIterator first, InputIterator last, ft::random_access_iterator_tag) {
   			return last - first;
		}
 
} // namespace detail
 
	template<class InputIterator>
		typename ft::iterator_traits<InputIterator>::difference_type 
    	distance(InputIterator first, InputIterator last) {	
    		return detail::do_distance(first, last,
                               typename ft::iterator_traits<InputIterator>::iterator_category());
		}

	/**
	 * @brief An iterator adaptor that reverses the direction of a given iterator
	 * 
	 * @tparam Iterator		Type of underlying iterator that should be RandomAccessIterator
	 */
	template <class Iterator>
		class reverse_rai_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
														typename iterator_traits<Iterator>::value_type,
														typename iterator_traits<Iterator>::difference_type,
														typename iterator_traits<Iterator>::pointer,
														typename iterator_traits<Iterator>::reference> {
														
		    typedef reverse_rai_iterator<Iterator> self;
			
		protected:
			Iterator iter_base;
			
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			
			reverse_rai_iterator(): iter_base() {}
			
			explicit reverse_rai_iterator(Iterator x): iter_base(x) {}
			
			template <class U>
				reverse_rai_iterator(const reverse_rai_iterator<U>& u): iter_base(u.base()) {};

			/* ?? Is it needed? Added to follow the subject */
            virtual ~reverse_rai_iterator() {}
						
			Iterator base() const { // explicit
				return iter_base;
			}
				
			reference operator*() const {
				return *(iter_base - 1);
			}
			
			pointer operator->() const {
				return &(operator*());
			}
			
			self& operator++() { //prefix
				--iter_base;
				return *this;
			}
			
			self operator++(int) { //postfix
				self tmp(*this);
				--iter_base;
				return tmp;
			}
			
			self& operator--() { //prefix
				++iter_base;
				return *this;
			}

			self operator--(int) { //postfix
				self tmp(*this);
				++iter_base;
				return tmp;
			}
			
			self& operator+=(difference_type n) {
				iter_base -= n;
				return *this;
			}
			
			self operator+ (difference_type n) const {
				self tmp(*this);
				tmp += n;
				return tmp;
			}

			self& operator-=(difference_type n){
				iter_base += n;
				return *this;
			}
			
			self operator- (difference_type n) const{
				self tmp(*this);
				tmp -= n;
				return tmp;
			}
			
			/**
			 * @param  n 	- 	position relative to current location. 
			 * @return A reference to the element at relative location
			 */
			reference operator[](difference_type n) const {
				return iter_base[-n-1];
			}
			
}; /*class reverse_rai_iterator*/

	
template <class Iterator>
	inline bool operator==(const reverse_rai_iterator<Iterator>& lhs, const reverse_rai_iterator<Iterator>& rhs){
		return lhs.base() == rhs.base();
	}
	
template <class Iterator>
	inline bool operator<(const reverse_rai_iterator<Iterator>& lhs, const reverse_rai_iterator<Iterator>& rhs){
		return rhs.base() < lhs.base();
	}

template <class Iterator>
	inline bool operator!=(const reverse_rai_iterator<Iterator>& lhs, const reverse_rai_iterator<Iterator>& rhs){
		return lhs.base() != rhs.base();
	}
	
template <class Iterator>
	inline bool operator>(const reverse_rai_iterator<Iterator>& lhs, const reverse_rai_iterator<Iterator>& rhs){
		return lhs.base() < rhs.base();
	}
	
template <class Iterator>
	inline bool operator>=(const reverse_rai_iterator<Iterator>& lhs, const reverse_rai_iterator<Iterator>& rhs){
		return lhs.base() <= rhs.base();
	}

template <class Iterator>
	inline bool operator<=(const reverse_rai_iterator<Iterator>& lhs, const reverse_rai_iterator<Iterator>& rhs){
		return lhs.base() >= rhs.base();
	}
	
template <class Iterator>
	inline typename reverse_rai_iterator<Iterator>::difference_type
			operator-(const reverse_rai_iterator<Iterator>& lhs,
						const reverse_rai_iterator<Iterator>& rhs){
		return rhs.base() - lhs.base();				
	}
						
template <class Iterator>
	inline reverse_rai_iterator<Iterator> operator+(typename reverse_rai_iterator<Iterator>::difference_type n,
											const reverse_rai_iterator<Iterator>& rhs){
		reverse_rai_iterator<Iterator> tmp(rhs.base()); 	
		tmp += n;
		return tmp;				
	}
	
} /* namespace ft*/

#endif /*ITERATOR_H*/