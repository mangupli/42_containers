#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

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

		typedef random_access_iterator<T>						iterator;
		typedef random_access_iterator< T const >				const_iterator;
		typedef reverseIterator<iterator>						reverse_iterator;
		typedef reverseIterator<const_iterator>					const_reverse_iterator;


	private:

		pointer			_ptr;
		size_type		_capacity;
		size_type		_size;
		allocator_type	_alloc;

	public:

/*
 * ---------------------------CONSTRUCTORS--------------------------------------
 */

		explicit vector (const allocator_type& alloc = allocator_type()):
							_ptr(NULL), _capacity(0), _size(0), _alloc(alloc) {}

		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()):
						 _capacity(n), _size(n), _alloc(alloc)
		{
			_ptr = _alloc.allocate(n);
			for(int i = 0; i < n; ++i)
				_alloc.construct(_ptr + i, val);
			//_ptr + n = NULL; //??
		}

		//TODO:  разобраться, почему вызывается этот
/*
		template <class InputIterator>
			vector (InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				_size = distance(first, last);
				_capacity = _size;
				_ptr = _alloc.allocate(_capacity);
				for(int i = 0; i < _size; ++i)
				{
					_alloc.construct(_ptr + i, *first);
					++first;
				}
			}
*/


		vector (const vector& x): _alloc(x._alloc), _size(x._size), _capacity(x._capacity)
		{
			_ptr = _alloc.allocate(_capacity);
			for(int i = 0; i < _size; ++i)
				_alloc.construct(_ptr + i, x[i]);
		}


/*
* -----------------------------DESTRUCTOR---------------------------------------
* Destructs the vector.
* The destructors of the elements are called and the used storage is deallocated.
* Note, that if the elements are pointers, the pointed-to objects are not destroyed.
*/

		~vector()
		{
			for (int i = 0; i < _size; ++i) // TODO: size or capacity??
				_alloc.destroy(_ptr + i);
			_alloc.deallocate(_ptr,_capacity); // TODO:size or capacity?
		}

/*
* ----------------------ASSIGNMENT OPERATOR-------------------------------------
*/

		vector& operator=(const vector& x)
		{
			if (this != &x)
			{

				for (int i = 0; i < _size; ++i) // TODO: size or capacity??
					_alloc.destroy(_ptr + i);
				_alloc.deallocate(_ptr,_capacity); // TODO:size or capacity?

				_size = x._size;
				_capacity = x.capacity;
				_alloc = x._alloc;

				_ptr = _alloc.allocate(_capacity);
				for(int i = 0; i < _size; ++i)
					_alloc.construct(_ptr + i, x[i]);
			}
			return *this;
		}

/*
 * -----------------------------CAPACITY----------------------------------------
 */
		size_type		max_size() const { return _alloc.max_size(); }
		bool			empty() const { return begin() == end(); }
		size_type		size() const { return _size; }
		void			reserve( size_type new_cap );
		size_type		capacity() const { return _capacity; }

/*
 * -----------------------------ITERATORS---------------------------------------
 */

		iterator				begin() { return iterator(_ptr); }
		const_iterator			begin() const { return const_iterator(_ptr); }
		iterator				end() { return iterator(_ptr + _size); }
		const_iterator			end() const { return const_iterator(_ptr + _size); }

		reverse_iterator		rbegin() { return reverse_iterator(_ptr); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(_ptr); }
		reverse_iterator		rend() { return reverse_iterator(_ptr + _size); }
		const_reverse_iterator	rend() const {
			return const_reverse_iterator(_ptr + _size); }

/*
 * --------------------------ELEMENT ACCESS-------------------------------------
 */

		reference operator[] (size_type n) { return _ptr[n]; }
		const_reference operator[] (size_type n) const { return _ptr[n]; }
		reference at (size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("out of range");
			return _ptr[n];
		}
		const_reference at (size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("out of range");
			return _ptr[n];
		}
		reference front(){ return *_ptr; }
		const_reference front() const { return *_ptr; }
		reference back(){ return _ptr[_size - 1]; }
		const_reference back() const { return _ptr[_size - 1]; }

	};



	
}


#endif