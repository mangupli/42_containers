/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:38:00 by mangupli          #+#    #+#             */
/*   Updated: 2022/07/27 23:54:12 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
#define STACK_H

#include <vector>

namespace ft
{
	/**
	* @tparam T 			The type of the stored elements. 
	* @tparam Container		The type of the underlying container to use to store the elements.
	*/
	
	template < class T, class Container = std::vector<T> >
	class stack
	{		

/*
*---------------------------MEMBER TYPES-------------------------------
*/

public:
		typedef Container						container_type;
		typedef typename Container::value_type	value_type;
		typedef typename Container::size_type	size_type;


/*
 * ---------------------MEMBER TYPE--------------------------------------
 */
protected:	
		container_type c;


/*
 * ---------------------------CONSTRUCTOR--------------------------------
 */

public:
		explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}


/*
 * ---------------------------DESTRUCTOR---------------------------------
 */
 		~stack() {}

/*
 * -----------------------MEMBER FUNCTIONS--------------------------------
 */
	
		bool				empty() const						{ return c.empty(); }
		size_type			size() const						{ return c.size(); }
		value_type&			top()								{ return c.back(); }
		const value_type&	top() const							{ return c.back(); }
		void				push(const value_type & x)			{ c.push_back(x); }
		void				pop()								{ c.pop_back(); }

/*
 * --------------NON-MEMBER COMPATISON FUNCTIONS----------------------------
 */	
	template <class Tt, class Cont>
	friend bool operator== (const stack<Tt,Cont>& lhs, const stack<Tt,Cont>& rhs);
	template <class Tt, class Cont>
	friend bool operator<  (const stack<Tt,Cont>& lhs, const stack<Tt,Cont>& rhs);
	
	}; /*class stack*/

	template <class T, class Container>
	inline bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	inline bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (lhs.c < rhs.c);
	}
	
	
	template <class T, class Container>
	inline bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return !(lhs == rhs);
	}	


	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return !(rhs < lhs);
	}
	
	template <class T, class Container>
	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (rhs < lhs);
	}
	
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return !(lhs < rhs);
	}
	
} /*namespace ft*/

#endif /* STACK_H*/