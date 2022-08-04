/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:29:01 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/04 23:26:00 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "iterator.hpp"
# include "utils.hpp"
# include "tree.hpp"

# include <memory>

namespace ft{

template<

	class Key,
	class T,
	class Compare = ft::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> >
> class map {

/*
 * --------------------MEMBER TYPES-------------------------------------
 */

public:
	typedef Key									key_type;
	typedef T									mapped_type;
	typedef ft::pair<const Key, T>				value_type;
	typedef Compare								key_compare;	
	typedef Allocator                       	allocator_type;
	typedef typename Allocator::reference   	reference;
	typedef typename Allocator::const_reference const_reference;



	class value_compare {
		friend class map;
	protected:
		Compare comp;
		value_compare(Compare c) : comp(c) {}
	public:
		bool operator()(const value_type& x, const value_type& y) const {
			return comp(x.first, y.first);
		}
	};
	
private:
	
	typedef ft::rb_tree<key_type,
						value_type,
						ft::select1st<value_type, key_type>,
						key_compare,
						allocator_type > tree_type;
	tree_type _tree;
	
public:
	typedef typename tree_type::pointer						pointer;
	typedef typename tree_type::const_pointer				const_pointer;
	typedef typename tree_type::size_type					size_type;
	typedef typename tree_type::difference_type				difference_type;
	typedef typename tree_type::iterator		 			iterator;
	typedef typename tree_type::const_iterator 				const_iterator;
	typedef typename tree_type::reverse_iterator			reverse_iterator;
	typedef typename tree_type::onst_reverse_iterator		const_reverse_iterator;
	

/*
 * ----------------CONSTRUCT/COPY/DESTROY-------------------------------------
 */

	explicit map(const key_compare& comp = Compare(),
				const allocator_type& alloc = Allocator())
					: _tree(comp, alloc) {}
			
	template <class InputIterator>
		map(InputIterator first, InputIterator last,
				const Compare& comp = Compare(),
				const Allocator& alloc = Allocator())
					: _tree(first, last, comp, alloc) {}
/*
				
	map(const map<Key,T,Compare,Allocator>& x);
	~map();
	map<Key,T,Compare,Allocator>&
		operator=(const map<Key,T,Compare,Allocator>& x);
*/

/*
 * ----------------CONSTRUCT/COPY/DESTROY-------------------------------------
 */
	iterator		begin()			{ return _tree.begin();}
	const_iterator	begin() const	{ return _tree.begin();}
	iterator		end()			{ return _tree.end();}
	const_iterator	end() const		{ return _tree.end();}

	reverse_iterator		rbegin()		{ return _tree.rbegin();}
	const_reverse_iterator	rbegin() const	{ return _tree.rbegin();}
    reverse_iterator		rend()			{ return _tree.rend();}
	const_reverse_iterator	rend() const	{ return _tree.rend();}

	
/*
 * -------------------------CAPACITY-------------------------------------
 */

	bool empty() const { return _tree.empty(); }
	size_type size() const { return _tree.size(); }
	size_type max_size() const { return _tree.max_size; }

/*
// 23.3.1.2 element access:
T& operator[](const key_type& x);
// modifiers:
pair<iterator, bool> insert(const value_type& x);
iterator insert(iterator position, const value_type& x);
template <class InputIterator>
void insert(InputIterator first, InputIterator last);
void erase(iterator position);
size_type erase(const key_type& x);
void erase(iterator first, iterator last);
void swap(map<Key,T,Compare,Allocator>&);
void clear();
// observers:
key_compare key_comp() const;
value_compare value_comp() const;
*/
/*
 * -------------------------CAPACITY-------------------------------------
 */

iterator find(const key_type& x){
	return _tree.find(x);
}

const_iterator find(const key_type& x) const{
	return _tree.find(x);
}

size_type count(const key_type& x) const{
	return _tree.size;
}

iterator lower_bound(const key_type& x){
	return _tree.lower_bound(x);
}

const_iterator lower_bound(const key_type& x) const{
	return _tree.lower_bound(x);
}

iterator upper_bound(const key_type& x){
	return _tree.upper_bound(x);
}

const_iterator upper_bound(const key_type& x) const{
	return _tree.upper_bound(x);
}

pair<iterator,iterator> equal_range(const key_type& x){
	return _tree.equal_range(x);
}

pair<const_iterator,const_iterator>
	equal_range(const key_type& x) const{
		return _tree.equal_range(x);
	}
};/*
template <class Key, class T, class Compare, class Allocator>
bool operator==(const map<Key,T,Compare,Allocator>& x,
const map<Key,T,Compare,Allocator>& y);
template <class Key, class T, class Compare, class Allocator>
bool operator< (const map<Key,T,Compare,Allocator>& x,
const map<Key,T,Compare,Allocator>& y);
template <class Key, class T, class Compare, class Allocator>
bool operator!=(const map<Key,T,Compare,Allocator>& x,
const map<Key,T,Compare,Allocator>& y);
template <class Key, class T, class Compare, class Allocator>
bool operator> (const map<Key,T,Compare,Allocator>& x,
const map<Key,T,Compare,Allocator>& y);
template <class Key, class T, class Compare, class Allocator>
bool operator>=(const map<Key,T,Compare,Allocator>& x,
const map<Key,T,Compare,Allocator>& y);
template <class Key, class T, class Compare, class Allocator>
bool operator<=(const map<Key,T,Compare,Allocator>& x,
const map<Key,T,Compare,Allocator>& y);
// specialized algorithms:
template <class Key, class T, class Compare, class Allocator>
void swap(map<Key,T,Compare,Allocator>& x,
map<Key,T,Compare,Allocator>& y);
*/

} /*namespace ft*/

#endif /*MAP_H*/