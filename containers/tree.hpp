/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspyke <mspyke@student.21-school.ru >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 17:28:58 by mspyke            #+#    #+#             */
/*   Updated: 2022/08/03 21:04:15 by mspyke           ###   ########.fr       */
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
 *  (2) The header cell is maintained with links not only to the root
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
		node*		parent_ptr;
		node*		left_ptr;
		node*		right_ptr;
		
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

	static node_allocator_type			_nodeAlloc;     
	static value_allocator_type			_valueAlloc;



/*
*-------------------------ACCESSORS--------------------------
*/

/**
 * @details The header cell is maintained with links not only to the root
 * but also to the leftmost node of the tree, to enable constant time
 * begin(), and to the rightmost node of the tree;
 * 
 */

    link_type header;  
	
    link_type& root() { return parent(header); }
    link_type& root() const { return parent(header); }
    link_type& leftmost() { return left(header); }
    link_type& leftmost() const { return left(header); }
    link_type& rightmost() { return right(header); }
    link_type& rightmost() const { return right(header); }
    

/*
*-------------------------MEMBER VARIABLES--------------------------
*/

	/*
    bool insert_always;  					// controls whether an element already in the
                         					// tree is inserted again */

	size_type			node_count;			// keeps track of size of tree
	Compare				key_compare;
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
                // check for header
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
                // check for header
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


}; /*class map*/


} /*namespace ft*/

#endif/*TREE_H*/