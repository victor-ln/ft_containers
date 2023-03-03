/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef RBTREE_RBTREE_HPP_
#define RBTREE_RBTREE_HPP_

#include <memory>

#include "tree_node.hpp"
#include "../iterators/reverse_iter.hpp"
#include "../iterators/rb_tree_iter.hpp"
#include "../utility/pair.hpp"

namespace ft {

template <typename value_type, typename Compare, typename AllocTp>
class rb_tree {
 public:
    typedef size_t                                    size_type;
    typedef ptrdiff_t                                 difference_type;
    typedef Compare                                   key_compare;
    typedef AllocTp                                   allocator_type;
    typedef value_type&                               reference;
    typedef const value_type&                         const_reference;
    typedef value_type*                               pointer;
    typedef const value_type*                         const_pointer;

    typedef ft::rb_tree_iter<pointer>                 iterator;
    typedef ft::rb_tree_iter<const_pointer>           const_iterator;
    typedef ft::reverse_iter<iterator>                reverse_iterator;
    typedef ft::reverse_iter<const_iterator>          const_reverse_iterator;

    explicit rb_tree(const value_type& val) {
        _root = _TNULL = _allocator.allocate(1);
        _root->color = black;
        _root->left = 0;
        _root->right = 0;
        _root->data = val;
    }

    void insert(const value_type& val) {
        nodePtr node = _allocator.allocate(1);
        _allocator.construct(&node->data, val);
        node->parent = 0;
        node->left = _TNULL;
        node->right = _TNULL;
        node->color = red;

        NodePtr y = 0;
        NodePtr x = this->root;

        while (x != _TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (!y) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }
        if (!node->parent) {
            node->color = black;
            return;
        }
        if (!node->parent->parent) {
            return;
        }
        insertFix(node);
    }

    nodePtr search(const value_type& val) {
        return searchTreeHelper(this->root, KeyOfValue()(val));
    }

 private:
    using typename node<value_type>::nodePtr;

    typedef typename AllocTp::rebind<nodePtr>::other  nodeAllocator;

    nodePtr    _root;
    nodePtr    _TNULL;
    AllocTp    _allocator;
    Compare    _comp;
    size_type  _size;

    template <typename Key>
    struct KeyOfValue {
       const Key& operator()(const value_type& x) const {
          return (x.first);
       }
    };

    template <typename Key>
    nodePtr _searchHelper(nodePtr node, const Key& key) {
        if (node == _TNULL || key == node->data) {
            return node;
        }
        if (key < node->data) {
            return searchHelper(node->left, key);
        }
        return searchHelper(node->right, key);
    }

    void  _leftRotate(nodePtr x) {
        nodePtr y = x->right;
        x->right = y->left;
        if (y->left != _TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == _TNULL) {
            _root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void  _rightRotate(nodePtr x) {
        nodePtr y = x->left;
        x->left = y->right;
        if (y->right != _TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == _TNULL) {
            _root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void  _insertFix(nodePtr x) {
        nodePtr u;
        while (x->parent->color == red) {
            if (x->parent == x->parent->parent->right) {
                u = x->parent->parent->left;
                if (u->color == red) {
                    u->color = black;
                    x->parent->color = black;
                    x->parent->parent->color = red;
                    x = x->parent->parent;
                } else {
                    if (x == x->parent->left) {
                        x = x->parent;
                        _rightRotate(x);
                    }
                    x->parent->color = black;
                    x->parent->parent->color = red;
                    _leftRotate(x->parent->parent);
                }
            } else {
                u = x->parent->parent->right;

                if (u->color == red) {
                    u->color = black;
                    x->parent->color = black;
                    x->parent->parent->color = red;
                    x = x->parent->parent;
                } else {
                    if (x == x->parent->right) {
                        x = x->parent;
                        _leftRotate(x);
                    }
                    x->parent->color = black;
                    x->parent->parent->color = red;
                    _rightRotate(x->parent->parent);
                }
            }
            if (x == root) {
                break;
            }
        }
        root->color = black;
    }
};

}  /* namespace ft */

#endif   /* RBTREE_RBTREE_HPP_ */
