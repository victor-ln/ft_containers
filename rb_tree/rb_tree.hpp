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
    typedef AllocTp                                   allocator_type;
    typedef value_type&                               reference;
    typedef const value_type&                         const_reference;
    typedef value_type*                               pointer;
    typedef const value_type*                         const_pointer;

    typedef ft::rb_tree_iter<pointer>                 iterator;
    typedef ft::rb_tree_iter<const_pointer>           const_iterator;
    typedef ft::reverse_iter<iterator>                reverse_iterator;
    typedef ft::reverse_iter<const_iterator>          const_reverse_iterator;

    rb_tree() : size(0) {
        _root = _create_root_node(0, black);
    }

    void insert(reference new_data, insertMode mode = noReplace, nodePtr from = 0) {
        if (!from) {
            from = _root;
        }
        while (from->data) {
            if (_comp(new_data, *from->data)) {
                from = from->left;
            } else if (_comp(*from->data, new_data)) {
                from = from->right;
            } else if (!mode) {
                return;
            } else {
                break;
            }
        }
        if (from->data) {
            _data_alloc.destroy(from->data);
            _data_alloc.deallocate(from->data, 1);
        } else {
            ++_size;
        }
        if (!from->left) {
            _create_leaf_nodes(from);
        }
        from->data = _allocate_data(new_data);
        _balanceTree(from);
    }

    iterator search(const_reference data) {
        nodePtr x = _root;
        while (x->data) {
            if (_comp(data, *x->data)) {
                x = x->left;
            } else if (_comp(*x->data, data)) {
                x = x->right;
            } else {
                return iterator(x);
            }
        }
        return end();
    }

    iterator begin() {
        return nodeBase::minimum(_root);
    }

    iterator end() {
        return nodeBase::maximum(_root)->right;
    }

    const_iterator begin() const {
        return nodeBase::minimum(_root);
    }
    
    const_iterator end() const {
        return nodeBase::maximum(_root)->right;
    }

 private:
    typedef node<value_type>*                           nodePtr;
    typedef node<value_type>                            nodeBase;
    typedef typename AllocTp::rebind<nodePtr>::other    nodeAllocator;

    nodePtr         _root;
    nodeAllocator   _node_alloc;
    allocator_type  _data_alloc;
    Compare         _comp;
    size_type       _size;

    pointer _allocate_data(reference pair) {
        pointer new_data = _data_alloc.allocate(1);
        _data_alloc.construct(new_data, pair);
        return new_data;
    }

    nodePtr    _create_root_node(pointer new_data, nodeColor node_color = red) {
        nodePtr new_node = _node_alloc.allocate(1);
        _node_alloc.construct(new_node, node<value_type>(new_data, node_color));
        _create_leaf_nodes(new_node);
        return new_node;
    }

    void        _create_leaf_nodes(nodePtr new_node) {
        new_node->left = _node_alloc.allocate(1);
        _node_alloc.construct(new_node->left, node<value_type>());
        new_node->right = _node_alloc.allocate(1);
        _node_alloc.construct(new_node->right, node<value_type>());
    }

    void    _balanceTree(nodePtr node) {
        nodePtr parent = node->parent;
        nodePtr grand_parent = parent->parent;
        nodePtr sibling;

        if (parent->color == red) {
            if (parent == grand_parent->right) {
                sibling = grand_parent->left;
                if (sibling->color == red) {
                    sibling->color = black;
                    parent->color = black;
                    grand_parent->color = red;
                    _balanceTree(grand_parent);
                } else {
                    if (node == parent->left) {
                        _rightRotate(parent);
                    }
                    parent->color = black;
                    grand_parent->color = red;
                    _leftRotate(grand_parent);
                    return;
                }
            } else {
                sibling = grand_parent->right;
                if (sibling->color == red) {
                    sibling->color = black;
                    parent->color = black;
                    grand_parent->color = red;
                    _balanceTree(grand_parent);
                } else {
                    if (node == parent->right) {
                        _leftRotate(parent);
                    }
                    parent->color = black;
                    grand_parent->color = red;
                    _rightRotate(grand_parent);
                    return;
                }
            }
        }
        if (!grand_parent) {
            _root->color = black;
            return;
        }
        _balanceTree(parent);
    }

    
    void _leftRotate(nodePtr x) {
        nodePtr y = x->right;

        x->right = y->left;
        if (y->left) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (!x->parent) {
            _root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void _rightRotate(nodePtr x) {
        nodePtr y = x->left;

        x->left = y->right;
        if (y->right) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (!x->parent) {
            _root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }
};

}  /* namespace ft */

#endif   /* RBTREE_RBTREE_HPP_ */
