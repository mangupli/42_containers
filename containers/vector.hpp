/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 23:27:17 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/05 19:22:28 by mspyke           ###   ########.fr       */
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

		explicit vector (const allocator_type& alloc = allocator_type()):
							_ptr(0), _capacity(0), _size(0), _alloc(alloc) {}

		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()):
						 _capacity(n),
						 _size(n),
						 _alloc(alloc)
		{
			_ptr = _alloc.allocate(n);
			for(size_type i = 0; i < n; ++i)
				_alloc.construct(_ptr + i, val);
		}


		template <class InputIterator>
			vector (InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type(),
						typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type * = 0)
						 : _alloc(alloc) {
			/**
			 * TODO: что происходит, если last<first
			 */
			
				_size = static_cast<size_type>(ft::distance(first, last));
				_capacity = _size;
				_ptr = _alloc.allocate(_capacity);
				for(size_type i = 0; i < _size; ++i)
				{
					_alloc.construct(_ptr + i, *first);
					++first;
				}
			}

		vector (const vector& x): _capacity(x._size), _size(x._size),_alloc(x._alloc)
		{
			_ptr = _alloc.allocate(_capacity);
			for(size_type i = 0; i < _size; ++i)
				_alloc.construct(_ptr + i, x[i]);
		}


/*
* -----------------------------DESTRUCTOR---------------------------------------
* The destructors of the elements are called and the used storage is deallocated.
* Note, that if the elements are pointers, the pointed-to objects are not destroyed.
*/

		~vector()
		{
			for (size_type i = 0; i < _size; ++i) 
				_alloc.destroy(_ptr + i);
			if(_ptr)	
				_alloc.deallocate(_ptr,_capacity);
		}

/*
* ----------------------ASSIGNMENT OPERATOR-------------------------------------
*/

		vector& operator=(const vector& x)
		{
			if (this != &x)
			{

				for (size_type i = 0; i < _size; ++i) 
					_alloc.destroy(_ptr + i);
				if (_ptr)
					_alloc.deallocate(_ptr,_capacity); 

				_size = x._size;
				_capacity = x._size;
				_alloc = x._alloc;

				_ptr = _alloc.allocate(_capacity);
				for(size_type i = 0; i < _size; ++i)
					_alloc.construct(_ptr + i, x[i]);
			}
			return *this;
		}
/*
 * ---------------------------MEMBER FUNCTIONS---------------------------------
 */

template <class InputIterator>
	void assign(InputIterator first, InputIterator last,
					typename ft::enable_if< !ft::is_integral<InputIterator>::value >::type * = 0){
		clear();
			
		size_t new_cap = static_cast<size_type>(ft::distance(first, last));
		if(new_cap <= _capacity){
			ft::uninitialized_copy(_alloc, first, last, begin());
			_size = new_cap;
		}
		else {
			if(_ptr)
				_alloc.deallocate(_ptr, _capacity);
			pointer new_ptr = _alloc.allocate(new_cap);
			ft::uninitialized_copy(_alloc, first, last, iterator(new_ptr));
			_size = new_cap;
			_ptr = new_ptr;
			_capacity = new_cap;
		}		
	}

void assign(size_type n, const T& value){
	clear();
	if (n <= _capacity){
		ft::uninitialized_fill_n(_alloc, begin(), n, value);
		_size = n;
	}
	else {
		if(_ptr)
			_alloc.deallocate(_ptr, _capacity);
		pointer new_ptr = _alloc.allocate(n);
		ft::uninitialized_fill_n(_alloc, iterator(new_ptr), n, value);
		_size = n;
		_ptr = new_ptr;
		_capacity = n;
	}				
}

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
				if(_ptr)
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

		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin() ); }
		const_reverse_iterator	rend() const {
			return const_reverse_iterator(begin()); }

/*
 * --------------------------ELEMENT ACCESS-------------------------------------
 */

		reference operator[] (size_type n) { return _ptr[n]; }
		const_reference operator[] (size_type n) const { return _ptr[n]; }
		reference at (size_type n){
			if(n > _size)
				throw std::out_of_range("vecto::at: out of range");
			return(*(_ptr + n));
		}
		
		const_reference at (size_type n) const{
			if(n > _size)
				throw std::out_of_range("vecto::at: out of range");
			return(*(_ptr + n));
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
				if(_ptr)
					_alloc.deallocate(_ptr, _capacity);
				
				_ptr = new_ptr;
				_capacity = new_cap;
				++_size;
			}
			
			return iterator(_ptr + n);;
		}

		void insert(iterator position, size_type n, const T& value) {
			if(n == 0) return ;
			if(_capacity - _size >= n) {
				if(end() - position > static_cast<difference_type>(n)) {
					ft::uninitialized_copy(_alloc, end() - static_cast<difference_type>(n), end(), end());
					ft::copy_backward(position, end() - static_cast<difference_type>(n), end());
					ft::fill(position, position + static_cast<difference_type>(n), value);
				}
				else {
					ft::uninitialized_copy(_alloc, position, end(), position + static_cast<difference_type>(n));
					ft::fill(position, end(), value);
					ft::uninitialized_fill_n(_alloc, end(), n - static_cast<size_type>(end() - position), value);
				}
				_size += n;
			}
			else {
				size_type new_cap = _size + ft::max(_size, n);
				pointer new_ptr = _alloc.allocate(new_cap);
				ft::uninitialized_copy(_alloc, begin(), position, iterator(new_ptr));
				ft::uninitialized_fill_n(_alloc, iterator(new_ptr + (position - begin())), n, value);
				ft::uninitialized_copy(_alloc, position, end(), iterator(new_ptr + (position - begin() + static_cast<difference_type>(n))));
				ft::destroy(_alloc, begin(), end());
				if (_ptr)
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
					if (end() - position > static_cast<difference_type>(n)) {
						ft::uninitialized_copy(_alloc, end() - static_cast<difference_type>(n), end(), end());
						ft::copy_backward(position, end() - static_cast<difference_type>(n), end());
						ft::copy(first, last, position);
					}
					else {
						ft::uninitialized_copy(_alloc, position, end(), position + static_cast<difference_type>(n));
						for(difference_type i = 0; i < end() - position; ++i){
							*position++ = *first++;
						}
						ft::uninitialized_copy(_alloc, first, last, end());
						}
				_size += n;
				}
				else {
					size_type new_cap = size() + max(size(), n);
					pointer new_ptr = _alloc.allocate(new_cap);
					ft::uninitialized_copy(_alloc, begin(), position, iterator(new_ptr));
					ft::uninitialized_copy(_alloc, first, last, iterator(new_ptr + (position - begin())));
					ft::uninitialized_copy(_alloc, position, end(), iterator(new_ptr + (position - begin() + static_cast<difference_type>(n))));
					ft::destroy(_alloc, begin(), end());
					if (_ptr)
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

			pointer pos_ptr = &(*position);
			
			if (position + 1 == end()){
				pop_back();
				return end();
			}
			ft::copy(position + 1, end(), position);
			--_size;
			_alloc.destroy(_ptr + _size);
				
		return iterator(pos_ptr); 
		}

		iterator erase(iterator first, iterator last){

			if (last < first) throw std::logic_error("vector::erase : iterator last < iterator first");

			if (first == last) return last;

			if(last == end()) {
				while(first != end())
					pop_back();
				return end();
			}
			
			pointer first_ptr = &(*first);

			iterator result = ft::copy(last, end(), first);

			while(result != end())
					pop_back();

			return iterator(first_ptr);
		
		}

		void swap(vector<T,Allocator>& other) {
			
			ft::swap(_ptr, other._ptr);
			ft::swap(_size, other._size);
			ft::swap(_capacity, other._capacity);
			ft::swap(_alloc, other._alloc);
		}

		void clear(){
			for(size_type i = 0; i < _size; ++i){
				_alloc.destroy(_ptr + i);
			}
			_size = 0;
		}

	}; /* class vector */

	template< class T, class Alloc >
	void swap(ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
		lhs.swap(rhs);
	}

/*
 * --------------------COMPARISON OPERATORS---------------------------------
 */

	template< class T, class Alloc >
	bool operator==( const vector<T,Alloc>& lhs,
			                 const vector<T,Alloc>& rhs ){
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < rhs.size(); ++i){
			if (lhs[i] != rhs[i])
				return false;
		}
			
		return true;
	}

	template< class T, class Alloc >
	bool operator!=( const vector<T,Alloc>& lhs,
		                 const vector<T,Alloc>& rhs ){
		return !(lhs == rhs);
	}

	template< class T, class Alloc >
	bool operator<( const vector<T,Alloc>& lhs,
		                const vector<T,Alloc>& rhs ){
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template< class T, class Alloc >
	bool operator<=( const vector<T,Alloc>& lhs,
		                 const vector<T,Alloc>& rhs ){
		return !(lhs > rhs);
	}
	
	template< class T, class Alloc >
	bool operator>( const vector<T,Alloc>& lhs,
		                const vector<T,Alloc>& rhs ){
		return rhs < lhs;
	}

	template< class T, class Alloc >
	bool operator>=( const vector<T,Alloc>& lhs,
		                 const vector<T,Alloc>& rhs ){
		return !(lhs < rhs);
	}

	
} /*namespace ft */


#endif /*VECTOR_H*/
