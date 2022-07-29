/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:08:59 by mspyke            #+#    #+#             */
/*   Updated: 2022/07/30 01:18:01 by mspyke           ###   ########.fr       */
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


} /*namespace ft*/


#endif /* UTILS_H*/