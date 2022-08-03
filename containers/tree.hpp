/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:28:58 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/04 00:55:26 by mspyke           ###   ########.fr       */
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



template<typename Key, typename Value, typename KeyOfValue = ft::select1st<Key, Value>,
	typename Compare = ft::less<Key>, typename Alloc = std::allocator<Value> >
class rb_tree
{
protected:

/*
*-------------------------MEMBER TYPES--------------------------
*/
	
	enum color_type { red, black};

	struct node 
	{
		color_type	color_field;
		node*		parent_link;
		node*		left_link;
		node*		right_link;
		
	};
		
public:

    typedef Key												key_type;
    typedef Value											value_type;
	typedef Alloc											value_allocator_type;
    typedef typename value_allocator_type::pointer			pointer;
    typedef typename value_allocator_type::reference		reference;
    typedef typename value_allocator_type::const_reference	const_reference;

	typedef typename Alloc::template rebind< node >::other  node_allocator_type;

    typedef typename node_allocator_type::pointer			link_type;
    typedef typename node_allocator_type::size_type			size_type;
    typedef typename node_allocator_type::difference_type	difference_type;
	
	
/*
*-------------------------ALLOCATORS--------------------------
*/

protected:

	static node_allocator_type		_node_alloc;     
	static value_allocator_type		_value_alloc;

	link_type allocate_node(){return _node_alloc.allocate(1);}




/*
*-------------------------ACCESSORS--------------------------
*/

protected:

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

	/*
    bool insert_always;  					// controls whether an element already in the
                         					// tree is inserted again */

	size_type			_node_count;			// keeps track of size of tree
	Compare				_key_compare;
	static size_type	_number_of_trees;
    static link_type	NIL;				//that's where all the leaves are going to point at

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
    static reference value(link_type x) { return (*x).value_field; }
	
    static const key_type& key(link_type x) {
        return KeyOfValue()(value(x));
    }
	
    static color_type& color(link_type x) { 
        return (color_type&)(*x).color_field; }

		
    static link_type minimum(link_type x) {
        while (left(x) != NIL)
            x = left(x);
        return x;
    }
    static link_type maximum(link_type x) {
        while (right(x) != NIL)
            x = right(x);
        return x;
    }

/*
*-------------------------ITERATORS--------------------------
*/

public:

    class iterator : public ft::iterator< ft::bidirectional_iterator_tag, value_type > {
		/*
    friend class rb_tree<Key, Value, KeyOfValue, Compare>;
    friend class const_iterator;
	*/

    protected:
        link_type				node;
        iterator(link_type x) : node(x) {}
		
    public:
        iterator() {}
        bool operator==(const iterator& y) const { return node == y.node; }
        reference operator*() const { return value(node); }
        iterator& operator++() {
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
        iterator operator++(int) {
            iterator tmp = *this;
            ++*this;
            return tmp;
        }
        iterator& operator--() {
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
        iterator operator--(int) {
            iterator tmp = *this;
            --*this;
            return tmp;
        }
    }; /*class iterator*/

	class const_iterator 
        : public ft::iterator< ft::bidirectional_iterator_tag, value_type > {
			/*
    friend class rb_tree<Key, Value, KeyOfValue, Compare>;
    friend class iterator;
	*/
    protected:
        link_type node;
        const_iterator(link_type x) : node(x) {}
    public:
        const_iterator() {}
        const_iterator(const iterator& x) : node(x.node) {}
        bool operator==(const const_iterator& y) const { 
            return node == y.node; 
        }
        bool operator!=(const const_iterator& y) const { 
            return node != y.node; 
        }
        const_reference operator*() const { return value(node); }
        const_iterator& operator++() {
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
        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++*this;
            return tmp;
        }
        const_iterator& operator--() {
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
        const_iterator operator--(int) {
            const_iterator tmp = *this;
            --*this;
            return tmp;
        }
    }; /*class const_iterator*/

	typedef reverse_bidirectional_iterator<iterator> reverse_iterator; 
    typedef reverse_bidirectional_iterator<const_iterator> const_reverse_iterator;

/*
*-------------Constructors and destrcutors----------------------
*/

/**
 *  TODO: придумать, что с аллокаторами 
 * 
 */

private:



    void init() {
		
        ++_number_of_trees;
		
        _header = allocate_node();
        color(_header) = red;  // used to distinguish _header from root,                      
        root() = NIL;
        leftmost() = _header;
        rightmost() = _header;
    }

public:
    
    rb_tree(const Compare& comp = Compare(),
				const value_allocator_type& alloc = value_allocator_type()) 
           : _node_count(0), _key_compare(comp) { 
		init();
    }

	rb_tree(const value_type* first, const value_type* last, 
            const Compare& comp = Compare(),
			const value_allocator_type& alloc = value_allocator_type())
          : _node_count(0), _key_compare(comp) {
			
        init();
        insert(first, last);
    }
	
    rb_tree(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x)
				: _node_count(x._node_count), 
                 	_key_compare(x._key_compare) {
		++_number_of_trees;
        _header = allocate_node();
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
        //erase(begin(), end());
        if (--_number_of_trees == 0) {
            /*deallocate NIL*/
			NIL = 0;
        }
    }

	rb_tree<Key, Value, KeyOfValue, Compare>& 
        operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x);


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
		}


}; /*class map*/

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::link_type 
        rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::NIL = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::size_type 
        rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_number_of_trees = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::node_allocator_type
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_node_alloc;

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::value_allocator_type
		rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::_value_alloc;




} /*namespace ft*/

#endif/*TREE_H*/