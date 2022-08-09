/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:28:58 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/09 18:42:26 by mspyke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
#define TREE_H

/**
 *  Rb tree rules
 * 
 *  1. a node is either red or black
 *  2. the root and leaves (NIL) are black
 *  3. if a node is red, then its children are black
 *  4. all paths from a node to its NIL descendants
 * 		contain the same number of black nodes
 * 
 *           8                            B                  
 *        /     \                      /     \               
 *       5       15                   B       R               
 * 	    / \     /   \                / \     /   \                 
 *    nil nil  12     19           nil nil  B      B               
 *            /   \   /  \                 / \     / \          
 *          9    13 nil   23             R     R  nil  R    
 *        /  \   / \     /  \          /  \   / \     /  \  
 *     nil  nil nil nil nil nil     nil  nil nil nil nil nil
 *  
 * Notes:
 *  (1) The longest path (root to farthest NIL) is no more
 *  than twice the length of shortest path (root to nearest NIL)
 *   - Shortest path: all black nodes
 *   - Longest path: alernating red and black
 * 
 *  (2) The _header cell is maintained with links not only to the root
 * but also to the leftmost node of the tree, to enable constant time
 * begin(), and to the rightmost node of the tree;
 * 
 * (3) When a node being deleted has two children its successor node is
 * relinked into its place, rather than copied, so that the only
 * iterators invalidated are those referring to the deleted node.
 *
 */

#include <memory>
#include "iterator.hpp"
#include "utils.hpp"


namespace ft{

enum color_type {red, black};

template<typename T>
struct rb_tree_node
{
			
			typedef T					value_type;
			typedef rb_tree_node<T>*	link_type;
			
			value_type*		value_ptr;
		   	link_type		parent_link;
			link_type		left_link;
			link_type		right_link;
			enum color_type	color_field;
		
			/**
			** @brief Value.
			** Create a rb_tree_node with value defined by a copy of "val".
			*/
		   
			rb_tree_node (value_type* srcval = 0, link_type parent_link = 0,
					link_type left_link = 0, link_type right_link = 0)
			:
				value_ptr(srcval),
				parent_link(parent_link),
				left_link(left_link),
				right_link(right_link),
				color_field(red)
			{}

			virtual ~rb_tree_node() {}


			/*
			** @brief Compare two rb_tree_node to know
			** if they contains the same value.
			*/
			bool operator==(const rb_tree_node& other)
			{
				if (*value_ptr == *(other.value_ptr))
					return (true);
				return (false);
			}

			const value_type * getValue() const {
				return value_ptr;
			}

			value_type * getValue() {
				return value_ptr;
			}
			
	};

template<typename Key, typename Value/*pair<const Key, T>*/, typename KeyOfValue = ft::select1st<Value, Key>,
	typename Compare = ft::less<Key>, typename Alloc = std::allocator<Value> >
class rb_tree
{
protected:
	
	typedef rb_tree_node<Value>									node_type;
	typedef typename Alloc::template rebind< node_type >::other	node_allocator_type;
	
/*
*-------------------------MEMBER TYPES--------------------------
*/

public:
	typedef typename node_allocator_type::pointer			link_type;
	typedef typename node_allocator_type::size_type			size_type;
	typedef typename node_allocator_type::difference_type	difference_type;

	typedef Key												key_type;
	typedef Value											value_type;
	typedef Alloc											value_allocator_type;
	typedef typename value_allocator_type::pointer			pointer;
	typedef typename value_allocator_type::const_pointer	const_pointer;
	typedef typename value_allocator_type::reference		reference;
	typedef typename value_allocator_type::const_reference	const_reference;	

/*
*-------------------------ACCESSORS--------------------------
*/

//protected:

/**
 * @details The _header cell is maintained with links not only to the root
 * but also to the leftmost node of the tree, to enable constant time
 * begin(), and to the rightmost node of the tree;
 * 
 */

	link_type _header;  
	
	link_type& root() { return parent(_header); }
	link_type& root() const { return parent(_header); }
	link_type& leftmost() { return left(_header); }
	link_type& leftmost() const { return left(_header); }
	link_type& rightmost() { return right(_header); }
	link_type& rightmost() const { return right(_header); }
	

/*
*-------------------------MEMBER VARIABLES--------------------------
*/

	size_type			_node_count;			// keeps track of size of tree
	Compare				_key_compare;
	static size_type	_number_of_trees;
	static link_type	NIL;				//that's where all the leaves are going to point at

/*
*-------------------------ALLOCATORS--------------------------
*/

protected:

	/*static?*/ value_allocator_type	_value_alloc; 
	/*static?*/ node_allocator_type		_node_alloc;
		  
	link_type allocate_node()	{return _node_alloc.allocate(1);}
	pointer	allocate_value()	{return _value_alloc.allocate(1);}


	pointer	create_value(const value_type &value){
		pointer new_val = _value_alloc.allocate(1);
		_value_alloc.construct(new_val, value);
		return new_val;
	}

	void construct_node( link_type new_node, const value_type & value){
		pointer new_val = create_value(value);
		_node_alloc.construct(new_node, node_type(new_val, _header, NIL, NIL));
	}
		

	value_allocator_type get_allocator() const {return _value_alloc;}

/*
*-------------------------NODE GETTERS--------------------------
*/

	static link_type& left(link_type x) { 
		return (link_type&)((*x).left_link);
	}
	static link_type& right(link_type x) {
		return (link_type&)((*x).right_link); 
	}
	static link_type& parent(link_type x) {
		return (link_type&)((*x).parent_link);
	}
	static reference value(link_type x) { return *((*x).value_ptr); }
	
	static const key_type& key(link_type x) {
		return KeyOfValue()(value(x));
	}
	
	static color_type& color(link_type x) { 
		return (color_type&)(*x).color_field; }

		
	static link_type minimum(link_type x) {
		while (/*x!= NIL && */ left(x) != NIL)
			x = left(x);
		return x;
	}
	static link_type maximum(link_type x) {
		while (/*x != NIL && */right(x) != NIL)
			x = right(x);
		return x;
	}



/*
*-------------------------ITERATORS--------------------------
*/

public:

	class rb_tree_iterator;
	friend class rb_tree_iterator;

	class rb_tree_iterator : public ft::iterator< ft::bidirectional_iterator_tag, value_type > {

	friend class rb_tree<Key, Value, KeyOfValue, Compare, Alloc>;
	//friend class const_rb_tree_iterator;

	protected:
		link_type				node;
		rb_tree_iterator(link_type x) : node(x) {}
		
		
	public:
		
		rb_tree_iterator() {}
		bool operator==(const rb_tree_iterator&other) const { return node == other.node; }
		bool operator!=(const rb_tree_iterator& other) const { return !(node == other.node); }
		reference operator*() const { return value(node); }
		pointer operator->() const { return node->getValue(); }
		rb_tree_iterator& operator++() {
			if (right(node) != NIL) {
				node = right(node);
				while (left(node) != NIL)
					node = left(node);
			}
			else {
				link_type y = parent(node);
				while (node == right(y)) {
					node = y;
					y = parent(y);
				}
				if (right(node) != y) // necessary because of rightmost 
					node = y;
			}
			return *this;
		}
		rb_tree_iterator operator++(int) {
			rb_tree_iterator tmp = *this;
			++*this;
			return tmp;
		}
		rb_tree_iterator& operator--() {
			if (color(node) == red && parent(parent(node)) == node)  
				// check for _header which is end()
				node = right(node);   // return rightmost
			else if (left(node) != NIL) {
				link_type y = left(node);
				while (right(y) != NIL)
					y = right(y);
				node = y;
			} else {
				link_type y = parent(node);
				while (node == left(y)) {
					node = y;
					y = parent(y);
				}
				node = y;
			}
			return *this;
		}
		rb_tree_iterator operator--(int) {
			rb_tree_iterator tmp = *this;
			--*this;
			return tmp;
		}
	}; /*class rb_tree_iterator*/

	class const_rb_tree_iterator;
	friend class const_rb_tree_iterator;

	class const_rb_tree_iterator 
		: public ft::iterator< ft::bidirectional_iterator_tag, const value_type > {
	friend class rb_tree<Key, Value, KeyOfValue, Compare, Alloc>;
	//friend class rb_tree_iterator;

	protected:
		link_type node;
		const_rb_tree_iterator(link_type x) : node(x) {}
	public:
		const_rb_tree_iterator() {}
		const_rb_tree_iterator(const rb_tree_iterator& x) : node(x.node) {}
		bool operator==(const const_rb_tree_iterator& y) const { 
			return node == y.node; 
		}
		bool operator!=(const const_rb_tree_iterator& y) const { 
			return node != y.node; 
		}
		const_reference operator*() const  { return value(node); }
		const_pointer operator->() const { return node->getValue(); }

		const_rb_tree_iterator& operator++() {
			if (right(node) != NIL) {
				node = right(node);
				while (left(node) != NIL)
					node = left(node);
			} else {
				link_type y = parent(node);
				while (node == right(y)) {
					node = y;
					y = parent(y);
				}
				if (right(node) != y) // necessary because of rightmost 
					node = y;
			}
			return *this;
		}
		const_rb_tree_iterator operator++(int) {
			const_rb_tree_iterator tmp = *this;
			++*this;
			return tmp;
		}
		const_rb_tree_iterator& operator--() {
			if (color(node) == red && parent(parent(node)) == node)  
				// check for _header
				node = right(node);   // return rightmost
			else if (left(node) != NIL) {
				link_type y = left(node);
				while (right(y) != NIL)
					y = right(y);
				node = y;
			} else {
				link_type y = parent(node);
				while (node == left(y)) {
					node = y;
					y = parent(y);
				}
				node = y;
			}
			return *this;
		}
		const_rb_tree_iterator operator--(int) {
			const_rb_tree_iterator tmp = *this;
			--*this;
			return tmp;
		}
	}; /*class const_rb_tree_iterator*/
	
	typedef rb_tree_iterator								iterator;
	typedef const_rb_tree_iterator							const_iterator;
	typedef reverse_bidirectional_iterator<iterator>		reverse_iterator; 
	typedef reverse_bidirectional_iterator<const_iterator>	const_reverse_iterator;

/*
*-------------Constructors and destrcutors----------------------
*/

private:

	void init() {
		
		++_number_of_trees;

		if (NIL == 0) {
			NIL = allocate_node();
			_node_alloc.construct(NIL, node_type());			
			color(NIL) = black;
		}
		
		_header = allocate_node();
		_node_alloc.construct(_header, node_type());
		color(_header) = red; //color red used to distinguish _header from root,                      
		root() = NIL;
		leftmost() = _header;
		rightmost() = _header;
	}

public:
	
	rb_tree(const Compare& comp = Compare(),
				const value_allocator_type& alloc = value_allocator_type()) 
		   : _node_count(0),
		   _key_compare(comp),
		   _value_alloc(alloc),
		   _node_alloc(node_allocator_type()) { 
		init();
	}

	rb_tree(const value_type* first, const value_type* last, 
			const Compare& comp = Compare(),
			const value_allocator_type& alloc = value_allocator_type())
		  : _node_count(0),
		  _key_compare(comp),
		  _value_alloc(alloc),
		  _node_alloc(node_allocator_type()) {
			
		init();
		insert(first, last);
	}
	
	rb_tree(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x)
				: _node_count(x._node_count), 
				 	_key_compare(x._key_compare),
					_value_alloc(x._value_alloc),
					_node_alloc(x._node_alloc) {
						
		++_number_of_trees;
		_header = allocate_node();
		_node_alloc.construct(_header, node_type());
		color(_header) = red;
		root() = _copy(x.root(), _header); 
		if (root() == NIL) {
			leftmost() = _header;
			rightmost() = _header;
		} else {
			leftmost() = minimum(root());
			rightmost() = maximum(root());
		}
	}
	~rb_tree() {
		erase(begin(), end());
		_node_alloc.destroy(_header);
		_node_alloc.deallocate(_header, 1);
		if (--_number_of_trees == 0) {
			_node_alloc.destroy(NIL);
			_node_alloc.deallocate(NIL, 1);
			NIL = 0;
		}
}
	rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& 
		operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x){
			if (this != &x) {
            	erase(begin(), end());
        		root() = _copy(x.root(), _header);
        		if (root() == NIL) {
            		leftmost() = _header;
            		rightmost() = _header;
        		} else {
	    		leftmost() = minimum(root());
            	rightmost() = maximum(root());
        		}
        	_node_count = x._node_count;
    	}
    	return *this;
	}


/*
*-------------------------ACCESSORS--------------------------
*/

	Compare key_comp() const { return _key_compare; }
	iterator begin() { return leftmost(); }
	const_iterator begin() const { return leftmost(); }
	iterator end() { return _header; }
	const_iterator end() const { return _header; }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { 
		return const_reverse_iterator(end()); 
	}
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { 
		return const_reverse_iterator(begin());
	}

/*
*-------------------------CAPACITY--------------------------
*/
	bool empty() const { return _node_count == 0; }
	size_type size() const { return _node_count; }
	size_type max_size() const { 
		return _node_alloc.max_size(); 
	}

	void swap(rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& other) {
			
			ft::swap(_header, other._header);
			ft::swap(_node_count, other._node_count);
			ft::swap(_key_compare, other._key_compare);
			ft::swap(_value_alloc, other._value_alloc);
			ft::swap(_node_alloc, other._node_alloc);
	}
	
/*
*-------------------------INSERT/ERASE--------------------------
*/

private:
/**
 * TODO: new allocation
 */
link_type _copy(link_type src, link_type dst) {
   // structural copy
   link_type res = src;
   while (src != NIL) {
      link_type tmp = allocate_node();
      if (res == src) res = tmp;  // save for return value
	  construct_node(tmp, value(src));
      left(dst) = tmp;
      parent(tmp) = dst;
      color(tmp) = color(dst);
      right(tmp) = _copy(right(src), tmp);
      dst = tmp;
      src = left(src);
   }
   left(dst) = NIL;
   return res;
}

	iterator _insert(link_type target_link, link_type parent_node, const Value & value){
	
		link_type new_node = allocate_node();
		construct_node(new_node, value);/*the new_node is always red in the beggining*/

		/*update header*/
		if (parent_node == _header || target_link != NIL || _key_compare(KeyOfValue()(value), key(parent_node))) {
			left(parent_node) = new_node;  // also makes leftmost() = new_node when parentt_nod == header
			if (parent_node == _header) {
				root() = new_node;
				rightmost() = new_node;
			} else if (parent_node == leftmost())
				leftmost() = new_node;   // maintain leftmost() pointing to minimum node
		} else {
			right(parent_node) = new_node;
			if (parent_node == rightmost())
				rightmost() = new_node;   // maintain rightmost() pointing to maximum node
		}
		
		/*set the links in the new_node*/
		parent(new_node) = parent_node;
		
		/* start to rebalance and recolor the tree*/
		target_link = new_node;
		
		/*while loop until we don't reach the root or the parent is still red*/
		link_type uncle;
		while (target_link != root() && color(parent(target_link)) == red){
			/*first we need to see which uncle(right or left) is needed*/
			if (parent(target_link) == left(parent(parent(target_link)))) {
				uncle = right(parent(parent(target_link)));
				if (color(uncle) == red) {
					color(parent(target_link)) = black;
					color(uncle) = black;
					color(parent(parent(target_link))) = red;
					target_link = parent(parent(target_link));
				} else {
					if (target_link == right(parent(target_link))) {
						target_link = parent(target_link);
						rotate_left(target_link);
					}
				color(parent(target_link)) = black;
				color(parent(parent(target_link))) = red;
				rotate_right(parent(parent(target_link)));
			}
		} else {
			uncle = left(parent(parent(target_link)));
			if (color(uncle) == red) {
				color(parent(target_link)) = black;
				color(uncle) = black;
				color(parent(parent(target_link))) = red;
				target_link = parent(parent(target_link));
			} else {
				if (target_link == left(parent(target_link))) {
					target_link = parent(target_link);
					rotate_right(target_link);
				}
				color(parent(target_link)) = black;
				color(parent(parent(target_link))) = red;
				rotate_left(parent(parent(target_link)));
				}
			}
		}
		/*in case it's the first element in the tree it didn't enter the loop so we change it to black
		and alыo during the recoloring the root might become red*/
		color(root()) = black; 
		++_node_count;
		
		return iterator(new_node);
	}


public:
	
	//typedef  pair<iterator, bool> pair_iterator_bool; 
	ft::pair<iterator, bool> insert(const value_type& value){
		
		link_type parent_node = _header;
		link_type current = root();
		
		bool comp = true;

		while(current != NIL){
			parent_node = current;
			comp = _key_compare(KeyOfValue()(value), key(current));
			current = comp ? left(current) : right(current);
		}
		iterator before = iterator(parent_node);
		if(comp){
			if(before == begin())
				return ft::pair<iterator, bool>(_insert(current, parent_node, value), true);
			else 
				--before;
		}
		if(_key_compare(key(before.node), KeyOfValue()(value)))
			return ft::pair<iterator, bool>(_insert(current, parent_node, value), true);
		return ft::pair<iterator, bool>(before, false);
	}

	iterator	insert(iterator hint, const value_type& value){
		if (hint == iterator(begin())){
			if (size() > 0 && _key_compare(KeyOfValue()(value), key(hint.node))) {
				return _insert(hint.node, hint.node, value);
				//return _insert(hint.node, leftmost(), value);
			} else
				return insert(value).first;
		} else if (hint == iterator(end())){
				if (_key_compare(key(rightmost()), KeyOfValue()(value)))
					return _insert(NIL, rightmost(), value);
				else
					return insert(value).first;
		} else {
			iterator before = --hint;
			if (_key_compare(key(before.node), KeyOfValue()(value))
						&& _key_compare(KeyOfValue()(value), key(hint.node))){
				if (right(before.node) == NIL)
					return _insert(NIL, before.node, value); 
				else
					return _insert(hint.node, hint.node, value);
			} else
				return insert(value).first;
		}
	}

	
	void		insert(iterator first, iterator last){
		while (first != last) {
			insert(*first);
			++first;
		}
	}
	
	void		insert(const value_type* first, const value_type* last){
		while (first != last) {
			insert(*first);
		}
	}
private:

	void		_erase_node(link_type n)
	{
			if(n->value_ptr){
				_value_alloc.destroy(n->value_ptr);
				_value_alloc.deallocate(n->value_ptr, 1);
				n->value_ptr = 0;
			}
			_node_alloc.destroy(n);
			_node_alloc.deallocate(n, 1);
	}

	void		_erase(link_type n){ /*erases node and its childs without rebalancing*/
		while(n != NIL){
			_erase(right(n));
			link_type tmp = left(n);
			_erase_node(n);
			n = tmp;
		}
	};

	void	_eraseFixup(link_type xxx){
		
		link_type w;
		
		while (xxx != root() && color(xxx) == black) {
				if (xxx == left(parent(xxx))) {
					
					w = right(parent(xxx));
					
					if (color(w) == red){ /*recolor and rotation needed then*/
						color(w) = black;
						color(parent(xxx)) = red;
						rotate_left(parent(xxx));
						w = right(parent(xxx));
					}
					
					if (color(left(w)) == black && color(right(w)) == black) {
						color(w) = red;
						xxx = parent(xxx);
					} else {
						if (color(right(w)) == black) {
							color(left(w)) = black;
							color(w) = red;
							rotate_right(w);
							w = right(parent(xxx));
						}
						color(w) = color(parent(xxx));
						color(parent(xxx)) = black;
						color(right(w)) = black;
						rotate_left(parent(xxx));
						break;
					}
				} else {  // same as then clause with "right" and "left" exchanged
					w = left(parent(xxx));
					if (color(w) == red) {
						color(w) = black;
						color(parent(xxx)) = red;
						rotate_right(parent(xxx));
						w = left(parent(xxx));
					}
					if (color(right(w)) == black && color(left(w)) == black) {
						color(w) = red;
						xxx = parent(xxx);
					} else {
						if (color(left(w)) == black) {
							color(right(w)) = black;
							color(w) = red;
							rotate_left(w);
							w = left(parent(xxx));
						}
						color(w) = color(parent(xxx));
						color(parent(xxx)) = black;
						color(left(w)) = black;
						rotate_right(parent(xxx));
						break;
					}
				}
			}
			color(xxx) = black;
	}
/*
	void _relink(link_type src, link_type dst){
		if(root() == src)
			root() = dst;
		else if (left(parent(src)) == src)
			left(parent(src)) = dst;
		else
			right(parent(src)) = dst;
		if(dst != NIL){
			parent(src) = parent(dst);
		}
			
	}
	*/
	
public:
	void		erase(iterator position){
		
		    
    	link_type orig_to_erase = position.node;
    	link_type replace = orig_to_erase;
    	link_type xxx;
		
    	if (left(replace) == NIL)
    	    xxx = right(replace);
    	else if (right(replace) == NIL) 
    	    xxx = left(replace);
    	else {
    	        replace = right(replace);
    	        while (left(replace) != NIL)
    	            replace = left(replace);
    	        xxx = right(replace);
    	}
       
    	if (replace != orig_to_erase) { // relink replace in place of orig_to_erase
    	    parent(left(orig_to_erase)) = replace; 
    	    left(replace) = left(orig_to_erase);
    	    if (replace != right(orig_to_erase)) {
    	        parent(xxx) = parent(replace); // possibly xxx == NIL
    	        left(parent(replace)) = xxx;   // replace must be a left child
    	        right(replace) = right(orig_to_erase);
    	        parent(right(orig_to_erase)) = replace;
    	    } else
    	        parent(xxx) = replace;  // needed in case xxx == NIL
				
    	    if (root() == orig_to_erase)
    	        root() = replace;
    	    else if (left(parent(orig_to_erase)) == orig_to_erase)
    	        left(parent(orig_to_erase)) = replace;
    	    else 
    	        right(parent(orig_to_erase)) = replace;
				
    	    parent(replace) = parent(orig_to_erase);
    	    ft::swap(color(replace), color(orig_to_erase));
    	    replace = orig_to_erase;
    	                   // replace points to node to be actually deleted
    	} else {  // replace == orig_to_erase
        	parent(xxx) = parent(replace);   // possibly xxx == NIL
			
        	if (root() == orig_to_erase)
        	    root() = xxx;
        	else {
        	    if (left(parent(orig_to_erase)) == orig_to_erase)
        	        left(parent(orig_to_erase)) = xxx;
        	    else
        	        right(parent(orig_to_erase)) = xxx;
			}
		
        	if (leftmost() == orig_to_erase){ 
        	    if (right(orig_to_erase) == NIL)  // left(orig_to_erase) must be NIL also
        	        leftmost() = parent(orig_to_erase);
        	        // makes leftmost() == header if orig_to_erase == root()
        		else
        	    	leftmost() = minimum(xxx);
			}
			
        	if (rightmost() == orig_to_erase)  {
        	    if (left(orig_to_erase) == NIL) // right(orig_to_erase) must be NIL also
        	        rightmost() = parent(orig_to_erase);  
        	        // makes rightmost() == header if orig_to_erase == root()
        		else  // xxx == left(orig_to_erase)
        	    rightmost() = maximum(xxx);
			}
    	}	
			
		if (color(replace) == black) { 
			_eraseFixup(xxx);
		}
	
		_erase_node(replace);
		--_node_count;
	
	}
	
	size_type	erase(const key_type& x){
		iterator position = find(x);
		if(position != end())
			erase(position);
		return (position != end());
	}
	
	void		erase(iterator first, iterator last) {
	if (first == begin() && last == end() && _node_count != 0) {
		_erase(root());
		leftmost() = _header;
		root() = NIL;
		rightmost() = _header;
		_node_count = 0;
	} else
		while (first != last) {
			erase(first);
			++first;
		}
	}

	void clear(){
		erase(begin(), end());
	}


/*
*--------------------------SEARCH----------------------------
*/

iterator find(const key_type& x){
	link_type last_not_less_than_x = _header; 
   	link_type current_node = root(); 

   while (current_node != NIL){
		if (!_key_compare(key(current_node), x)){
			last_not_less_than_x = current_node;
			current_node = left(current_node);
		} else {
			current_node = right(current_node);
		}      
	}
	iterator j = iterator(last_not_less_than_x);   
   	return (j == end() || _key_compare(x, key(j.node))) ? end() : j;
}

const_iterator find(const key_type& x) const {
	link_type last_not_less_than_x = _header; 
   	link_type current_node = root(); 

   while (current_node != NIL){
		if (!_key_compare(key(current_node), x)){
			last_not_less_than_x = current_node;
			current_node = left(current_node);
		} else {
			current_node = right(current_node);
		}      
	}
	const_iterator j = const_iterator(last_not_less_than_x);   
   	return (j == end() || _key_compare(x, key(j.node))) ? end() : j;
}

size_type count(const key_type& x) const{
	ft::pair<const_iterator, const_iterator> range = equal_range(x);
	size_type n = ft::distance(range.first, range.second);
	return n;
}

iterator lower_bound(const key_type& x){
	link_type last_not_less_than_x = _header;
	link_type current_node = root();

	while(current_node != NIL){
		if(!_key_compare(key(current_node), x)){
			last_not_less_than_x = current_node;
			current_node = left(current_node);
		} else {
			current_node = right(current_node);
		}
	}
	return iterator(last_not_less_than_x);
}

const_iterator lower_bound(const key_type& x) const{
	link_type last_not_less_than_x = _header;
	link_type current_node = root();

	while(current_node != NIL){
		if(!_key_compare(key(current_node), x)){
			last_not_less_than_x = current_node;
			current_node = left(current_node);
		} else {
			current_node = right(current_node);
		}
	}
	return const_iterator(last_not_less_than_x);
}

iterator upper_bound(const key_type& x){
	link_type last_greater_than_x = _header;
	link_type current_node = root();

	while(current_node != NIL){
		if(_key_compare(x, key(current_node))){
			last_greater_than_x = current_node;
			current_node = left(current_node);
		} else {
			current_node = right(current_node);
		}
	}
	return iterator(last_greater_than_x);
}
const_iterator upper_bound(const key_type& x) const{
	link_type last_greater_than_x = _header;
	link_type current_node = root();

	while(current_node != NIL){
		if(_key_compare(x, key(current_node))){
			last_greater_than_x = current_node;
			current_node = left(current_node);
		} else {
			current_node = right(current_node);
		}
	}
	return const_iterator(last_greater_than_x);
}
 
ft::pair<iterator,iterator> equal_range(const key_type& x){
	return ft::make_pair<iterator, iterator>(lower_bound(x), upper_bound(x));
}

pair<const_iterator,const_iterator> equal_range(const key_type& x) const{
	return ft::make_pair<const_iterator, const_iterator>(lower_bound(x), upper_bound(x));
}

/*
*--------------------------ROTATIONS----------------------------
*/

	void rotate_left(link_type x) {
		link_type y = right(x);
		right(x) = left(y);
		if (left(y) != NIL)
			parent(left(y)) = x;
		parent(y) = parent(x);
		if (x == root())
			root() = y;
		else if (x == left(parent(x)))
			left(parent(x)) = y;
		else
			right(parent(x)) = y;
		left(y) = x;
		parent(x) = y;
	}

	void rotate_right(link_type x) {
		link_type y = left(x);
		left(x) = right(y);
		if (right(y) != NIL)
			parent(right(y)) = x;
		parent(y) = parent(x);
		if (x == root())
			root() = y;
		else if (x == right(parent(x)))
			right(parent(x)) = y;
		else
			left(parent(x)) = y;
		right(y) = x;
		parent(x) = y;
	}


}; /*class rb_tree*/

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::link_type 
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::NIL = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::size_type 
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_number_of_trees = 0;


template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
bool operator==(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x,
				const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& y)
{
	return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
}

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
bool operator<(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x,
				const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& y)
{
	return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}


} /*namespace ft*/

#endif/*TREE_H*/