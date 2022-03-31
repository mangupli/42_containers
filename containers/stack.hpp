#ifndef STACK_H
#define STACK_H

#include <vector>

namespace ft
{
	template < class T, class Container = std::vector<T> >
	class stack
	{		
/*
*------------------------------MEMBER TYPES--------------------------------------
*/	   	
public:

		typedef Container						container_type;
		typedef typename Container::value_type	value_type;
		typedef typename Container::size_type	size_type;


/*
*------------------------------MEMBER OBJECT-------------------------------------
*/
protected:		
		container_type c;
/*
*------------------------------CONSTRUCTOR---------------------------------------
*/
public:
		explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}
/*
*------------------------------DESCTRUCTOR---------------------------------------
*/
 		~stack() {}
/*
*-----------------------------MEMBER FUNCTIONS-----------------------------------
*/
	
	bool				empty() const						{ return c.empty(); }
	size_type			size() const						{ return c.size(); }
	value_type&			top()								{ return c.back(); }
	const value_type&	top() const							{ return c.back(); }
	void				push(const value_type & x)			{ c.push_back(x); }
	void				pop()								{ c.pop_back(); }

/*
*-----------------------------NON MEMBER FUNCTIONS---------------------------------
*/		

//Both containers, lhs and rhs, are accessed. 

	template <class Tt, class Cont>
	friend bool operator== (const stack<Tt,Cont>& lhs, const stack<Tt,Cont>& rhs);
	template <class Tt, class Cont>
	friend bool operator!= (const stack<Tt,Cont>& lhs, const stack<Tt,Cont>& rhs);	
	template <class Tt, class Cont>
	friend bool operator<  (const stack<Tt,Cont>& lhs, const stack<Tt,Cont>& rhs);
	template <class Tt, class Cont>
	friend bool operator<= (const stack<Tt,Cont>& lhs, const stack<Tt,Cont>& rhs);
	template <class Tt, class Cont>
	friend bool operator>  (const stack<Tt,Cont>& lhs, const stack<Tt,Cont>& rhs);
	template <class Tt, class Cont>
	friend bool operator>= (const stack<Tt,Cont>& lhs, const stack<Tt,Cont>& rhs);
	

	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (lhs.c == rhs.c);
	}
	
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (lhs.c != rhs.c);
	}	

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (lhs.c < rhs.c);
	}
	
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (lhs.c <= rhs.c);
	}
	
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (lhs.c > rhs.c);
	}
	
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
		return (lhs.c >= rhs.c);
	}
}

#endif