/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:08:59 by mspyke            #+#    #+#             */
/*   Updated: 2022/07/30 13:52:11 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H


namespace ft {
	
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



template<typename T>
bool check_integral_function(T x){
	return ft::is_integral<T>::value;
}
 
/* end of is_integral*/

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last,
				   ForwardIterator result) {
    while (first != last) construct(&*result++, *first++);
    return result;
}

template <class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, 
			const T& x) {
    while (first != last) construct(&*first++, x);
}

template <class ForwardIterator, class Size, class T>
ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n,
				     const T& x) {
    while (n--) construct(&*first++, x);
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


} /*namespace ft*/


#endif /* UTILS_H*/