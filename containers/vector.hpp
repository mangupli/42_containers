#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

#include "random_access_iterator.hpp"
#include "utils.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{

	public:
/*
*---------------------------MEMBER TYPES-------------------------------
*/

		typedef T												value_type;
		typedef Allocator		   								allocator_type;
		typedef size_t											size_type;
		typedef ptrdiff_t										difference_type;

		typedef value_type&										reference;
		typedef  const value_type&								const_reference;

		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;

		typedef random_access_iterator<value_type>				iterator;
		typedef random_access_iterator< value_type const >		const_iterator;
		typedef reverse_rai_iterator<iterator>					reverse_iterator;
		typedef reverse_rai_iterator<const_iterator>			const_reverse_iterator;


	private:

		pointer			_ptr;
		size_type		_capacity;
		size_type		_size;
		allocator_type	_alloc;
	public:

/*
 * ---------------------------CONSTRUCTORS--------------------------------------
 */

		explicit vector (const allocator_type& _alloc = allocator_type()):
							_ptr(NULL), _capacity(0), _size(0), _alloc(_alloc) {}

		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()):
						 _capacity(n),
						 _size(n),
						 _alloc(alloc)
		{
			_ptr = _alloc.allocate(n);
			for(int i = 0; i < n; ++i)
				_alloc.construct(_ptr + i, val);
			//_ptr + n = NULL; //??
		}


		template <class InputIterator>
			vector (InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type(),
						typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type * = 0)
						 : _alloc(alloc) {
			/**
			 * TODO: что происходит, если last<first
			 */
			
				_size = ft::distance(first, last);
				_capacity = _size;
				_ptr = _alloc.allocate(_capacity);
				for(int i = 0; i < _size; ++i)
				{
					_alloc.construct(_ptr + i, *first);
					++first;
				}
			}



		vector (const vector& x): _alloc(x._alloc), _size(x._size), _capacity(x._capacity)
		{
			_ptr = _alloc.allocate(_capacity);
			for(int i = 0; i < _size; ++i)
				_alloc.construct(_ptr + i, x[i]);
		}


/*
* -----------------------------DESTRUCTOR---------------------------------------
* The destructors of the elements are called and the used storage is deallocated.
* Note, that if the elements are pointers, the pointed-to objects are not destroyed.
*/

		~vector()
		{
			for (int i = 0; i < _size; ++i) /** TODO: _size or _capacity??*/
				_alloc.destroy(_ptr + i);
			_alloc.deallocate(_ptr,_capacity); /** TODO:_size or _capacity?*/
		}

/*
* ----------------------ASSIGNMENT OPERATOR-------------------------------------
*/

		vector& operator=(const vector& x)
		{
			if (this != &x)
			{

				for (int i = 0; i < _size; ++i) /** TODO:_size or _capacity?*/
					_alloc.destroy(_ptr + i);
				_alloc.deallocate(_ptr,_capacity); /** TODO:_size or _capacity?*/

				_size = x._size;
				_capacity = x._capacity;
				_alloc = x._alloc;

				_ptr = _alloc.allocate(_capacity);
				for(int i = 0; i < _size; ++i)
					_alloc.construct(_ptr + i, x[i]);
			}
			return *this;
		}

/*
 * --------------------------MEMBER FUCNTIONS-----------------------------------
 */
		size_type		max_size() const { return _alloc.max_size(); }
		bool			empty() const { return begin() == end(); }
		size_type		size() const { return _size; }
		size_type		capacity() const { return _capacity; }
		void			reserve( size_type new_cap );

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

/*
Header <vector> synopsis
namespace std {
template <class T, class _allocator = _allocator<T> > class vector;
template <class T, class _allocator>
bool operator==(const vector<T,_allocator>& x,
const vector<T,_allocator>& y);
template <class T, class _allocator>
bool operator< (const vector<T,_allocator>& x,
const vector<T,_allocator>& y);
template <class T, class _allocator>
bool operator!=(const vector<T,_allocator>& x,
const vector<T,_allocator>& y);
template <class T, class _allocator>
bool operator> (const vector<T,_allocator>& x,
const vector<T,_allocator>& y);
template <class T, class _allocator>
bool operator>=(const vector<T,_allocator>& x,
const vector<T,_allocator>& y);
template <class T, class _allocator>
bool operator<=(const vector<T,_allocator>& x,
const vector<T,_allocator>& y);
template <class T, class _allocator>
void swap(vector<T,_allocator>& x, vector<T,_allocator>& y);
template <class _allocator> class vector<bool,_allocator>;
template <class _allocator>
bool operator==(const vector<bool,_allocator>& x,
const vector<bool,_allocator>& y);
template <class _allocator>
bool operator< (const vector<bool,_allocator>& x,
const vector<bool,_allocator>& y);
template <class _allocator>
bool operator!=(const vector<bool,_allocator>& x,
const vector<bool,_allocator>& y);
template <class _allocator>
bool operator> (const vector<bool,_allocator>& x,
const vector<bool,_allocator>& y);
template <class _allocator>
bool operator>=(const vector<bool,_allocator>& x,
const vector<bool,_allocator>& y);
template <class _allocator>
bool operator<=(const vector<bool,_allocator>& x,
const vector<bool,_allocator>& y);
template <class _allocator>
void swap(vector<bool,_allocator>& x, vector<bool,_allocator>& y);
}
*/