/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:08:59 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/01 15:16:43 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdexcept>


namespace ft {

template <typename T>
    void swap(T& a, T& b)
	{
		T	c;

		c = a;
		a = b;
		b = c;
	}

template<typename T>
const T& max(const T & a, const T & b){
    return a < b ? b : a;
}
	
template<typename T, T value_>
struct integral_constant{
	static const T value = value_;
};

struct false_type: ft::integral_constant<bool, false> {};
struct true_type: ft::integral_constant<bool, true> {};

template<bool B, typename T = void>
	struct enable_if{};
template<typename T>
	struct enable_if<true, T>{ typedef T type;};

template<class T, class U>
	struct is_same : public ft::false_type {};
template<class T>
	struct is_same<T, T> : public ft::true_type {};

template< class T > struct remove_const                { typedef T type; };
template< class T > struct remove_const<const T>       { typedef T type; };

/**
 * 
 * @brief My implementation of std::is_integral.
 * 
 *  
 * @details Quote form the standart^ "Types bool, char, wchar_t, and the signed and unsigned integer types
 * are collectively called integral types.  A synonym for integral type is integer type.
 * The representations of integral types shall define values by use of a pure binary numeration system. 
 */

template<typename T> struct is_integral_base			: ft::false_type{};
template<> struct is_integral_base<char>				: ft::true_type{};
template<> struct is_integral_base<signed char>			: ft::true_type{};
template<> struct is_integral_base<unsigned char>		: ft::true_type{};
template<> struct is_integral_base<int>					: ft::true_type{};
template<> struct is_integral_base<unsigned int>		: ft::true_type{};
template<> struct is_integral_base<short int>			: ft::true_type{};
template<> struct is_integral_base<long int>			: ft::true_type{};
template<> struct is_integral_base<unsigned short int>	: ft::true_type{};
template<> struct is_integral_base<unsigned long int>	: ft::true_type{};
template<> struct is_integral_base<wchar_t>				: ft::true_type{};
template<> struct is_integral_base<bool>				: ft::true_type{};



template<typename T> struct is_integral: ft::is_integral_base<T>{};


/*
template<typename T>
bool check_integral_function(T x){
	return ft::is_integral<T>::value;
}
*/
 
/* end of is_integral*/


template <class Alloc, class ForwardIterator>
void destroy(Alloc & alloc, ForwardIterator first, ForwardIterator last) {
    while (first != last) {
	    alloc.destroy(&*first);
	    ++first;
    }
}

template <class Alloc, class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(Alloc & alloc, InputIterator first, InputIterator last,
				   ForwardIterator result) {
    while (first != last) alloc.construct(&*result++, *first++);
    return result;
}

template <class Alloc, class ForwardIterator, class T>
void uninitialized_fill(Alloc & alloc, ForwardIterator first, ForwardIterator last, 
			const T& x) {
    while (first != last) alloc.construct(&*first++, x);
}

template <class Alloc, class ForwardIterator, class Size, class T>
ForwardIterator uninitialized_fill_n(Alloc & alloc,ForwardIterator first, Size n,
				     const T& x) {
    while (n--) alloc.construct(&*first++, x);
    return first;
}

template <class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last,
		    OutputIterator result) {
    while (first != last) *result++ = *first++;
    return result;
}       

template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, 
				     BidirectionalIterator1 last, 
				     BidirectionalIterator2 result) {
    while (first != last) *--result = *--last;
    return result;
}

template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value) {
    while (first != last) *first++ = value;
}

template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
    while (n-- > 0) *first++ = value;
    return first;
}

template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (*first1 < *first2) return true;
        if (*first2 < *first1) return false;
    }
    return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                             InputIt2 first2, InputIt2 last2,
                             Compare comp)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
        if (comp(*first1, *first2)) return true;
        if (comp(*first2, *first1)) return false;
    }
    return (first1 == last1) && (first2 != last2);
}




} /*namespace ft*/


#endif /* UTILS_H*/