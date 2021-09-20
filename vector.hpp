#ifndef VECTOR_H
#define VECTOR_H

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:

		//---------------------------MEMBER TYPES-------------------------------

		typedef T				value_type;
		typedef Allocator		allocator_type;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;

		typedef T &				reference;
		typedef T const &		const_reference;
		typedef T *				pointer;
		typedef T const *		const_pointer;

		//iterator
		//const_iterator
		//reverse_iterator
		//const_reverse_iterator

		vector();
		explicit vector( const Allocator& alloc );
		explicit vector( size_type count,
						 const T& value = T(),
						 const Allocator& alloc = Allocator());


	};








}


#endif