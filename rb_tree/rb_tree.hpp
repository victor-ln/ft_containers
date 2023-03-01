/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef RBTREE_RBTREE_HPP_
#define RBTREE_RBTREE_HPP_

#include <memory>

#include "tree_node.hpp"
#include "../utility/pair.hpp"

#define RBTREE_TEMPLATE typename Key, typename T, typename Compare, typename AllocTp
#define RBTREE_CLASS ft::rb_tree<Key, T, Compare, AllocTp>

namespace ft {

template <typename Key, typename T, typename Compare, typename AllocTp>
class rb_tree {
 private:
    using typename node<T>::nodePtr;

    typedef Key                                       key_type;
    typedef	T                                         mapped_type;
    typedef ft::pair<const Key, T>                    value_type;
    typedef size_t                                    size_type;
    typedef ptrdiff_t                                 difference_type;
    typedef Compare                                   key_compare;
    typedef AllocTp                                   allocator_type;
    typedef value_type&                               reference;
    typedef const value_type&                         const_reference;
    typedef value_type*                               pointer;
    typedef const value_type*                         const_pointer;

    typedef ft::map_iterator<pointer>                 iterator;
    typedef ft::map_iterator<const_pointer>           const_iterator;
    typedef ft::reverse_iterator<iterator>            reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>      const_reverse_iterator;

    typedef typename AllocTp::rebind<nodePtr>::other  nodeAllocator;

    nodePtr    _root;
    nodePtr    _rootBase;
    AllocTp    _allocator;
    size_type  _size;

 public:
    explicit rb_tree(const value_type&);
};

}   // namespace ft

#include "rb_tree.tpp"

#endif  // RBTREE_RBTREE_HPP_
