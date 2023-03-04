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

    void swap(rb_tree& src) {
        nodePtr         tmp_root(src._root);
        nodeAllocator   tmp_node_alloc(src._node_alloc);
        allocator_type  tmp_data_alloc(src._data_alloc);
        Compare         tmp_comp(src._comp);
        size_type       tmp_size(src._size);

        src._root = _root;
        src._node_alloc = _node_alloc;
        src._data_alloc = _data_alloc;
        src._comp = _comp;
        src._size = _size;

        _root = tmp_root;
        _node_alloc = tmp_node_alloc;
        _data_alloc = tmp_data_alloc;
        _comp = tmp_comp;
        _size = tmp_size;
    }

    void clear(void) {
        clear_recursive(_root);
    }

    void clear_recursive(nodePtr node) {
        if (node) {
            clear_recursive(node->left);
            clear_recursive(node->right);
            if (node->data) {
                _data_alloc.deallocate(node->data);
                _data_alloc.destroy(node->data, 1);
            }
            _node_alloc.deallocate(node);
            _node_alloc.destroy(node, 1);
        }
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
        if (from != _root) {
            _balance_tree(from);
        }
    }

    bool    remove(const_reference data) {
        nodePtr node_to_delete = search(data);
        if (!node_to_delete) {
            return false;
        }
        nodePtr x, y = node_to_delete;
        nodeColor y_color = y->color;
        if (!node_to_delete->left) {
            x = node_to_delete->right;
            _transplant(node_to_delete, node_to_delete->right);
        } else if (!node_to_delete->right) {
            x = node_to_delete->left;
            _transplant(node_to_delete, node_to_delete->left);
        } else {
            y = nodeBase::minimum(node_to_delete->right);
            y_color = y->color;
            x = y->right;
            if (node_to_delete != node_to_delete->right) {
                _transplant(y, y->right);
                y->right = node_to_delete->right;
                y->right->parent = y;
            } else {
                x->parent = y;
            }
            _transplant(node_to_delete, y);
            y->left = node_to_delete->left;
            y->left->parent = y;
            y->color = node_to_delete->color;
        }
        _node_alloc.destroy(node_to_delete);
        _node_alloc.deallocate(node_to_delete, 1);
        if (y_color == black) {
            remove_fix(x);
        }
        --_size;
        return true;
    }

    nodePtr search(const_reference data) {
        nodePtr x = _root;
        while (x->data) {
            if (_comp(data, *x->data)) {
                x = x->left;
            } else if (_comp(*x->data, data)) {
                x = x->right;
            } else {
                return x;
            }
        }
        return 0;
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

    void _transplant(NodePtr u, NodePtr v) {
        if (u->parent == 0) {
            _root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void    _balance_tree(nodePtr node) {
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
                    _balance_tree(grand_parent);
                } else {
                    if (node == parent->left) {
                        _right_rotate(parent);
                    }
                    parent->color = black;
                    grand_parent->color = red;
                    _left_rotate(grand_parent);
                    return;
                }
            } else {
                sibling = grand_parent->right;
                if (sibling->color == red) {
                    sibling->color = black;
                    parent->color = black;
                    grand_parent->color = red;
                    _balance_tree(grand_parent);
                } else {
                    if (node == parent->right) {
                        _left_rotate(parent);
                    }
                    parent->color = black;
                    grand_parent->color = red;
                    _right_rotate(grand_parent);
                    return;
                }
            }
        }
        if (!grand_parent) {
            _root->color = black;
            return;
        }
        _balance_tree(parent);
    }

    void remove_fix(nodePtr node) {
        if (!node || node->color == red) {
            return;
        }
        nodePtr parent = node->parent;
        nodePtr sibling = (node == parent->left) ? parent->right : parent->left;

        if (sibling->color == red) {
            sibling->color = black;
            parent->color = red;
            if (node == parent->left) {
                _left_rotate(parent);
            } else {
                _right_rotate(parent);
            }
            sibling = (node == parent->left) ? parent->right : parent->left;
        }
        if ((!sibling->left || sibling->left->color == black) &&
            (!sibling->right || sibling->right->color == black)) {
            sibling->color = red;
            _remove_fix(parent);
        } else {
            if (node == parent->left &&
                (!sibling->right || sibling->right->color == black)) {
                sibling->left->color = black;
                sibling->color = red;
                _right_rotate(sibling);
                sibling = parent->right;
            } else if (node == parent->right &&
                        (!sibling->left || sibling->left->color == black)) {
                sibling->right->color = black;
                sibling->color = red;
                _left_rotate(sibling);
                sibling = parent->left;
            }

            sibling->color = parent->color;
            parent->color = black;
            if (node == parent->left) {
                sibling->right->color = black;
                _left_rotate(parent);
            } else {
                sibling->left->color = black;
                _right_rotate(parent);
            }
        }
    }

    void _left_rotate(nodePtr x) {
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

    void _right_rotate(nodePtr x) {
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
