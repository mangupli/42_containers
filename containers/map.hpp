/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:29:01 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/06 18:00:09 by mspyke           ###   ########.fr       */
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
	typedef typename tree_type::const_reverse_iterator		const_reverse_iterator;
	

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

				
	map(const map<Key,T,Compare,Allocator>& other): _tree(other._tree){}
	
	~map();
	
	map<Key,T,Compare,Allocator>&
		operator=(const map<Key,T,Compare,Allocator>& other){
		if (this != &other)
			_tree = other._tree;
		return *this;
	}


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
 * -------------------------ELEMENT ACCESS--------------------------------
*/

	mapped_type& operator[] (const key_type& k)
		{ return (*((this->insert(value_type(k,mapped_type()))).first)).second;}

/*
 * ------------------------MODIFIERS-------------------------------------
 */

pair<iterator, bool> insert(const value_type& x){
	return _tree.insert(x);
}

iterator insert(iterator hint, const value_type& x){
	return _tree.insert(hint, x);
}

template <class InputIterator>
void insert(InputIterator first, InputIterator last);


void erase(iterator position){
	_tree.erase(position);
}

size_type erase(const key_type& x){
	return _tree.erase(x);
}

void erase(iterator first, iterator last){
	_tree.erase(first, last);
}

void swap(map<Key,T,Compare,Allocator>&other){
	_tree.swap(other._tree);
}

void clear(){
	_tree.clear();
}


/*
 * ------------------------OBSERVERS-------------------------------------
 */
key_compare key_comp() const {return _tree.key_comp;}
value_compare value_comp() const {return _tree.key_comp;}


/*
 * -------------------------SEARCH-------------------------------------
 */

iterator find(const key_type& x){
	return _tree.find(x);
}

const_iterator find(const key_type& x) const{
	return _tree.find(x);
}

size_type count(const key_type& x) const{
	return _tree.count(x);
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
};
/*
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