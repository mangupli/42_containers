#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
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

		typedef random_access_iterator<T>						iterator;
		typedef random_access_iterator< T const >				const_iterator;
		typedef reverseIterator<iterator>						reverse_iterator;
		typedef reverseIterator<const_iterator>					const_reverse_iterator;


	private:

		pointer			ptr;
		size_type		capacity;
		size_type		size;
		allocator_type	alloc;

	public:

/*
 * ---------------------------CONSTRUCTORS--------------------------------------
 */

		explicit vector (const allocator_type& alloc = allocator_type()):
							ptr(NULL), capacity(0), size(0), alloc(alloc) {}

		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()):
						 capacity(n), size(n), alloc(alloc)
		{
			ptr = alloc.allocate(n);
			for(int i = 0; i < n; ++i)
				alloc.construct(ptr + i, val);
			//ptr + n = NULL; //??
		}

		//TODO:  разобраться, почему вызывается этот
/*
		template <class InputIterator>
			vector (InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type()) : alloc(alloc)
			{
				size = distance(first, last);
				capacity = size;
				ptr = alloc.allocate(capacity);
				for(int i = 0; i < size; ++i)
				{
					alloc.construct(ptr + i, *first);
					++first;
				}
			}
*/


		vector (const vector& x): alloc(x.alloc), size(x.size), capacity(x.capacity)
		{
			ptr = alloc.allocate(capacity);
			for(int i = 0; i < size; ++i)
				alloc.construct(ptr + i, x[i]);
		}


/*
* -----------------------------DESTRUCTOR---------------------------------------
* The destructors of the elements are called and the used storage is deallocated.
* Note, that if the elements are pointers, the pointed-to objects are not destroyed.
*/

		~vector()
		{
			for (int i = 0; i < size; ++i) /** TODO: size or capacity??*/
				alloc.destroy(ptr + i);
			alloc.deallocate(ptr,capacity); /** TODO:size or capacity?*/
		}

/*
* ----------------------ASSIGNMENT OPERATOR-------------------------------------
*/

		vector& operator=(const vector& x)
		{
			if (this != &x)
			{

				for (int i = 0; i < size; ++i) /** TODO:size or capacity?*/
					alloc.destroy(ptr + i);
				alloc.deallocate(ptr,capacity); /** TODO:size or capacity?*/

				size = x.size;
				capacity = x.capacity;
				alloc = x.alloc;

				ptr = alloc.allocate(capacity);
				for(int i = 0; i < size; ++i)
					alloc.construct(ptr + i, x[i]);
			}
			return *this;
		}

/*
 * --------------------------MEMBER FUCNTIONS-----------------------------------
 */
		size_type		maxsize() const { return alloc.maxsize(); }
		bool			empty() const { return begin() == end(); }
		size_type		size() const { return size; }
		size_type		capacity() const { return capacity; }
		void			reserve( size_type new_cap );

/*
 * -----------------------------ITERATORS---------------------------------------
 */

		iterator				begin() { return iterator(ptr); }
		const_iterator			begin() const { return const_iterator(ptr); }
		iterator				end() { return iterator(ptr + size); }
		const_iterator			end() const { return const_iterator(ptr + size); }

		reverse_iterator		rbegin() { return reverse_iterator(ptr); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(ptr); }
		reverse_iterator		rend() { return reverse_iterator(ptr + size); }
		const_reverse_iterator	rend() const {
			return const_reverse_iterator(ptr + size); }

/*
 * --------------------------ELEMENT ACCESS-------------------------------------
 */

		reference operator[] (size_type n) { return ptr[n]; }
		const_reference operator[] (size_type n) const { return ptr[n]; }
		reference at (size_type n)
		{
			if (n >= size)
				throw std::out_of_range("out of range");
			return ptr[n];
		}
		const_reference at (size_type n) const
		{
			if (n >= size)
				throw std::out_of_range("out of range");
			return ptr[n];
		}
		reference front(){ return *ptr; }
		const_reference front() const { return *ptr; }
		reference back(){ return ptr[size - 1]; }
		const_reference back() const { return ptr[size - 1]; }

	};



	
}


#endif

/*
Header <vector> synopsis
namespace std {
template <class T, class Allocator = allocator<T> > class vector;
template <class T, class Allocator>
bool operator==(const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator< (const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator!=(const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator> (const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator>=(const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
bool operator<=(const vector<T,Allocator>& x,
const vector<T,Allocator>& y);
template <class T, class Allocator>
void swap(vector<T,Allocator>& x, vector<T,Allocator>& y);
template <class Allocator> class vector<bool,Allocator>;
template <class Allocator>
bool operator==(const vector<bool,Allocator>& x,
const vector<bool,Allocator>& y);
template <class Allocator>
bool operator< (const vector<bool,Allocator>& x,
const vector<bool,Allocator>& y);
template <class Allocator>
bool operator!=(const vector<bool,Allocator>& x,
const vector<bool,Allocator>& y);
template <class Allocator>
bool operator> (const vector<bool,Allocator>& x,
const vector<bool,Allocator>& y);
template <class Allocator>
bool operator>=(const vector<bool,Allocator>& x,
const vector<bool,Allocator>& y);
template <class Allocator>
bool operator<=(const vector<bool,Allocator>& x,
const vector<bool,Allocator>& y);
template <class Allocator>
void swap(vector<bool,Allocator>& x, vector<bool,Allocator>& y);
}
*/