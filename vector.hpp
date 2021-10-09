#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{

	public:
/*
*---------------------------MEMBER TYPES-------------------------------
*/

		typedef T				value_type;
		typedef Alloc		    allocator_type;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;

		// typedef T &				reference;
		// typedef T const &		const_reference;
		// typedef T *				pointer;
		// typedef T const *		const_pointer;

        typedef typename allocator_type::reference           	reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;

		//iterator
		//const_iterator
		//reverse_iterator
		//const_reverse_iterator


	private:

		pointer			_ptr;
		size_type		_capacity;
		size_type		_size;
		allocator_type	_alloc;

	public:

/*
 * ---------------------------CONSTRUCTORS--------------------------------------
 */

		explicit vector (const allocator_type& alloc = allocator_type());
		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type());

		template <class InputIterator>
			vector (InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type());

		vector (const vector& x);

/*
 * -----------------------------CAPACITY----------------------------------------
 */

		size_type		max_size() const;
		bool			empty() const;
		size_type		size() const;
		void			reserve( size_type new_cap );
		size_type		capacity() const;







	};

/*
 * ---------------------------CONSTRUCTORS--------------------------------------
 */

	template < typename T, typename Alloc>
		vector<T, Alloc>::vector(const allocator_type& alloc): _alloc(alloc) {}




/*
 * -----------------------------CAPACITY----------------------------------------
 */

	template < typename T, typename Alloc>
		typename vector<T, Alloc>::size_type
		vector<T, Alloc>::max_size() const { return _alloc.max_size(); }

	template < typename T, typename Alloc>
		bool vector<T, Alloc>::empty() const { return _alloc.max_size(); }











}


#endif