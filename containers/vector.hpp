/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 23:27:17 by mspyke            #+#    #+#             */
/*   Updated: 2022/07/31 23:27:18 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				
				pointer new_ptr = _alloc.allocate(new_cap); /* TODO: what if new_cap == 0 */
				ft::uninitialized_copy(_alloc, begin(), end(), iterator(new_ptr));

				ft::destroy(_alloc, begin(), end());
				if (_capacity) 
					_alloc.deallocate(_ptr,_capacity);

				_ptr = new_ptr;
				_capacity = new_cap;
			}
		}

/**
 * @brief Doesn't change the objects that are already there(only when reallocate the memory)
 * but if sz > _size —> then appends new one with the value
 * 
 */
		void resize(size_type sz, T value = T()){

			if(sz > max_size()) {
				throw std::length_error("std::resize :  sz > max_size()");
			}

			if(sz > _capacity) {
				size_t new_cap = _capacity * 2 > sz ? _capacity * 2 : sz;
				reserve(new_cap);
			}

			for(size_type i = _size; i < sz; ++i) {
				_alloc.construct(_ptr + i, value);
			}
						
			for(size_t j = sz; j < _size; ++j){
				_alloc.destroy(_ptr + j);
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
			_alloc.construct(_ptr + _size, x);
			++_size;
		}

		void pop_back(){
			_alloc.destroy(_ptr + _size - 1);
			--_size;
		}

		/**
		 * @brief inserts value before position
		 * 
		 * @param position  iterator before which the content will be inserted. pos may be the end() iterator 
		 * @param value		element value to insert 
		 * @return Iterator pointing to the inserted value
		 */

		iterator insert(iterator position, const value_type& value){
			difference_type n = position - begin();
			if(_size < _capacity) {
				if (position == end()){
					push_back(value);
				}
				else {
					_alloc.construct(_ptr + _size, *(_ptr + _size - 1));
					ft::copy_backward(position, iterator(_ptr + _size - 1), iterator(_ptr + _size));
					*position = value;
					++_size;
				}
			}
			else if(_size == _capacity) {
				size_t new_cap = _capacity == 0? 1 : _capacity * 2;
				pointer new_ptr = _alloc.allocate(new_cap);
				ft::uninitialized_copy(_alloc, begin(), position, iterator(new_ptr));
				_alloc.construct(new_ptr + (position - begin()), value);
				ft::uninitialized_copy(_alloc, position, end(), iterator(new_ptr + (position - begin()) + 1));
				ft::destroy(_alloc, begin(), end());
				if (_capacity)
					_alloc.deallocate(_ptr, _capacity);
				
				_ptr = new_ptr;
				_capacity = new_cap;
				++_size;
			}
			
			return iterator(_ptr + n);; /*TODO: check*/
		}

		void insert(iterator position, size_type n, const T& value) {
			if(n == 0) return ;
			if(_capacity - _size >= n) {
				if(end() - position > n) {
					ft::uninitialized_copy(_alloc, end() - n, end(), end());
					ft::copy_backward(position, end() - n, end());
					ft::fill(position, position + n, value);
				}
				else {
					ft::uninitialized_copy(_alloc, position, end(), position + n);
					ft::fill(position, end(), value);
					ft::uninitialized_fill_n(_alloc, end(), n - (end() - position), value);
				}
				_size += n;
			}
			else {
				size_type new_cap = _size + ft::max(_size, n);
				pointer new_ptr = _alloc.allocate(new_cap);
				ft::uninitialized_copy(_alloc, begin(), position, iterator(new_ptr));
				ft::uninitialized_fill_n(_alloc, iterator(new_ptr + (position - begin())), n, value);
				ft::uninitialized_copy(_alloc, position, end(), iterator(new_ptr + (position - begin() + n)));
				ft::destroy(_alloc, begin(), end());
				if (_capacity)
					_alloc.deallocate(_ptr, _capacity);
				_ptr = new_ptr;
				_capacity = new_cap;
				_size += n;
			}
		}

		template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last,
						typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type * = 0){

				if (first == last) return;

				size_type n = static_cast<size_type>(ft::distance(first, last));
				if (_capacity - _size >= n) {
					if (end() - position > n) {
						ft::uninitialized_copy(_alloc, end() - n, end(), end());
						ft::copy_backward(position, end() - n, end());
						ft::copy(first, last, position);
					}
					else {
						ft::uninitialized_copy(_alloc, position, end(), position + n);
						ft::copy(first, first + (end() - position), position);
						ft::uninitialized_copy(_alloc, first + (end() - position), last, end());
						}
				_size += n;
				}
				else {
					size_type new_cap = size() + max(size(), n);
					pointer new_ptr = _alloc.allocate(new_cap);
					ft::uninitialized_copy(_alloc, begin(), position, iterator(new_ptr));
					ft::uninitialized_copy(_alloc, first, last, iterator(new_ptr + (position - begin())));
					ft::uninitialized_copy(_alloc, position, end(), iterator(new_ptr + (position - begin() + n)));
					ft::destroy(_alloc, begin(), end());
					if (_capacity)
						_alloc.deallocate(_ptr, _capacity);
					_ptr = new_ptr;
					_capacity = new_cap;
					_size += n;
    			}

			}

/**
 * @brief  Removes the element at pos.
 * 
 * @details Complexity is Linear: the number of calls to the destructor of T is
 *  the same as the number of elements erased,
 *	the assignment operator of T is called the number of times equal to
 *  the number of elements in the vector after the erased elements 
 * 
 * @param position - iterator to the element to remove 
 * @return Iterator following the last removed element. 
 */
		iterator erase(iterator position){

			if (position + 1 == end()){
				pop_back();
				return end();
			}
			iterator result = ft::copy(position + 1, end(), position);
			--_size;
			_alloc.destroy(_ptr + _size);
				
		return result; /** TODO: check the return value*/
		}

		iterator erase(iterator first, iterator last){

			if (last < first) throw std::logic_error("vector::erase : iterator last < iterator first");

			if (first == last) return last;

			if(last == end()) {
				while(first != end())
					pop_back();
				return end();
			}

			iterator result = ft::copy(last, end(), first);

			while(result != end())
					pop_back();

			return result;
		
		}

		void swap(vector<T,Allocator>&);

		void clear(){
			for(size_type i = 0; i < _size; ++i){
				_alloc.destroy(_ptr + i);
			}
			_size = 0;
		}

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