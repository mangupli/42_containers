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

		typedef ft::random_access_iterator<value_type>			iterator;
		typedef ft::random_access_iterator< value_type const >	const_iterator;
		typedef ft::reverse_rai_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_rai_iterator<const_iterator>		const_reverse_iterator;


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
			for (int i = 0; i < _size; ++i) 
				_alloc.destroy(_ptr + i);
			if(_capacity)
				_alloc.deallocate(_ptr,_capacity);
		}

/*
* ----------------------ASSIGNMENT OPERATOR-------------------------------------
*/

		vector& operator=(const vector& x)
		{
			if (this != &x)
			{

				for (int i = 0; i < _size; ++i) 
					_alloc.destroy(_ptr + i);
				if (_capacity)
					_alloc.deallocate(_ptr,_capacity); 

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
 * ---------------------------MEMBER FUNCTIONS---------------------------------
 */

template <class InputIterator>
	void assign(InputIterator first, InputIterator last){}

void assign(size_type n, const T& u){}

allocator_type get_allocator() const { return _alloc; }

/*
 * --------------------------------CAPACITY------------------------------------
 */
		size_type		max_size() const { return _alloc.max_size(); }
		bool			empty() const { return begin() == end(); }
		size_type		size() const { return _size; }
		size_type		capacity() const { return _capacity; }

		void			reserve( size_type new_cap ){

			if(new_cap > max_size()) {
				throw std::length_error("std::reserve :  new_cap > max_size()");
			}
			else if (_capacity < new_cap) {
				
				pointer new_ptr = _alloc.allocate(new_cap);
				size_type i = 0;
				try {
					for(; i < size; ++i){
						_alloc.construct(new_ptr + i, _ptr[i]);
				}
				} catch (...) {
					for(size_t j = 0; j < i; ++j){
						_alloc.destroy(new_ptr + j);
					}
					_alloc.deallocate(new_ptr, new_cap);
					throw;
				}

				for(size_t i = 0; i < size; ++i){
					_alloc.destroy(_ptr + i);
				}
				if (_capacity)
					_alloc.deallocate(_ptr,_capacity);

				_ptr = new_ptr;
				_capacity = new_cap;
			}
		}

		void resize(size_type sz, T value = T()){
			if(sz > capacity) {
				size_t new_cap = capacity * 2 > sz ? capacity * 2 : sz;
				reserve(new_cap);
			}

			size_t i = _size;
			try {
				for(; _size < sz; ++i) {
					_alloc.construct(_ptr + i, value);
				}
			}
			catch (...){
				for(size_t j = 0; j < i; ++j){
						_alloc.destroy(_ptr + j);
					}
				throw;
			}
			
			for(int i = sz; sz < _size; ++i){
				_alloc.destroy(_ptr + i);
			}

			_size = sz;
		}

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

/*
 * --------------------------MODIFIERS-------------------------------------
 */

		void push_back(const T& x){
			if(_capacity == _size) {
				size_t new_cap = _capacity == 0? 1 : _capacity * 2;
				reserve(new_cap);
			}
			_alloc.construct(_ptr + _size);
			++_size;
		}

		void pop_back();

		iterator insert(iterator position, const T& x);

		void insert(iterator position, size_type n, const T& x);

		template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last);

		iterator erase(iterator position);

		iterator erase(iterator first, iterator last);

		void swap(vector<T,Allocator>&);

		void clear();

	}; /* class vector */



	
} /*namespace ft */


#endif /*VECTOR_H*/

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