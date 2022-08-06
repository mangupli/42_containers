/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:29:04 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/06 13:57:50 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_H
# define PAIR_H

namespace ft{

template <class T1, class T2>
    struct pair {
        
        typedef T1 first_type;
        typedef T2 second_type;
        
        first_type      first;
	    second_type     second;
        
	    pair() : first(), second() {}
        
        template <class U, class V>
            pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}
            
	    pair(const pair & pr) : first(pr.first), second(pr.second) {}
        
        pair(const T1 &a, const T2 &b) : first(a), second(b) {}
        
        pair &operator=(const pair &pr) {
            first = pr.first;
            second = pr.second;
            return (*this);
        }
};

template <class T1, class T2>
inline bool operator==(const pair<T1, T2>& x, const pair<T1, T2>& y) { 
    return x.first == y.first && x.second == y.second; 
}

template <class T1, class T2>
inline bool operator<(const pair<T1, T2>& x, const pair<T1, T2>& y) { 
    return x.first < y.first || (!(y.first < x.first) && x.second < y.second); 
}

template <class T1, class T2>
inline pair<T1, T2> make_pair(const T1& x, const T2& y) {
    return pair<T1, T2>(x, y);
}

} /*namespace ft*/

#endif /*PAIR_H*/