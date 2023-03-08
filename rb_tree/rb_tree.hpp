/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef RBTREE_RBTREE_HPP_
#define RBTREE_RBTREE_HPP_

#include <memory>
#include <iostream>

#include "tree_node.hpp"
#include "../iterators/reverse_iter.hpp"
#include "../iterators/rb_tree_iter.hpp"
#include "../utility/pair.hpp"

namespace ft {

template <typename value_type,
          typename Compare,
          typename AllocTp = std::allocator<value_type> >
class rb_tree {
    typedef node<value_type>                            node_base;
    typedef node_base*                                  node_pointer;
    typedef const node_base*                            const_node_pointer;
    typedef node_base**                                 node_pointer_addr;
    typedef typename AllocTp::template
                    rebind<node_base>::other            node_allocator;

 public:
    typedef size_t                                      size_type;
    typedef ptrdiff_t                                   difference_type;
    typedef value_type&                                 reference;
    typedef const value_type&                           const_reference;
    typedef value_type*                                 pointer;
    typedef const value_type*                           const_pointer;
    typedef Compare                                     key_compare;

    typedef ft::rb_tree_iter<pointer>                   iterator;
    typedef ft::rb_tree_iter<const_pointer>             const_iterator;
    typedef ft::reverse_iter<iterator>                  reverse_iterator;
    typedef ft::reverse_iter<const_iterator>            const_reverse_iterator;

    rb_tree(const key_compare& comp, const AllocTp& allocator = AllocTp())
            :   _size(0),
                _comp(comp),
                _node_allocator(allocator) {
        _nil = _node_allocator.allocate(1);
        _node_allocator.construct(_nil, node_base());
        _nil->leaf = _nil;
        _nil->left = _nil;
        _nil->right = _nil;
        _root = _nil;
    }

    ~rb_tree() {
        clear();
        _node_allocator.destroy(_nil);
        _node_allocator.deallocate(_nil, 1);
    }

    void swap(rb_tree& src) {
        node_pointer        tmp_nil(src._nil);
        node_pointer        tmp_root(src._root);
        size_type           tmp_size(src._size);
        compare_functions   tmp_comp(src._comp);
        node_allocator      tmp_node_allocator(src._node_allocator);

        src._nil = _nil;
        src._root = _root;
        src._size = _size;
        src._comp = _comp;
        src._node_allocator = _node_allocator;

        _nil = tmp_nil;
        _root = tmp_root;
        _size = tmp_size;
        _comp = tmp_comp;
        _node_allocator = tmp_node_allocator;
    }

    size_type   size(void) const {
        return _size;
    }

    size_type   max_size(void) const {
        return _node_allocator.max_size();
    }

    iterator    begin(void) {
        return iterator(node_base::minimum(_root));
    }

    iterator    end(void) {
        return iterator(_nil);
    }

    const_iterator    begin(void) const {
        return const_iterator(node_base::minimum(_root));
    }

    const_iterator    end(void) const {
        return const_iterator(_nil);
    }

    void clear(void) {
        _clear_recursive(_root);
        _size = 0;
    }

    node_pointer    lower_bound(const_reference to_compare) {
        return _find_bound(to_compare, _comp.not_less);
    }

    node_pointer    upper_bound(const_reference to_compare) {
        return _find_bound(to_compare, _comp.greater);
    }

    const_node_pointer    search(const_reference data) const {
        const_node_pointer    node = _root;

        while (node != _nil) {
            if (_comp.less(data, node->data)) {
                node = node->left;
            } else if (_comp.greater(data, node->data)) {
                node = node->right;
            } else {
                return node;
            }
        }
        return 0;
    }

    node_pointer    search(const_reference data) {
        node_pointer    node = _root;

        while (node != _nil) {
            if (_comp.less(data, node->data)) {
                node = node->left;
            } else if (_comp.greater(data, node->data)) {
                node = node->right;
            } else {
                return node;
            }
        }
        return 0;
    }

    iterator    insert(const_reference data, node_pointer hint = 0) {
        node_pointer        parent = 0;
        node_pointer_addr   root_addr = _is_nil(hint) ? &_root : &hint;

        while (*root_addr != _nil) {
            parent = *root_addr;
            if (_comp.less((*root_addr)->data, data)) {
                root_addr = &(*root_addr)->right;
            } else if (_comp.greater((*root_addr)->data, data)) {
                root_addr = &(*root_addr)->left;
            } else {
                return iterator(*root_addr);
            }
        }
        *root_addr = _create_new_node(data, parent);
        _balance_tree_insert(*root_addr);
        _update_nil_insert(*root_addr);
        return iterator(*root_addr);
    }

    bool    remove(const_reference data) {
        node_pointer    node = search(data);
        if (!node) {
            return false;
        }
        node_pointer    x;
        nodeColor       old_color = node->color;

        if (node->left == _nil) {
            x = node->right;
            _transplant(node, node->right);
        } else if (node->right == _nil) {
            x = node->left;
            _transplant(node, node->left);
        } else {
            node_pointer    y = node_base::minimum(node->right);
            old_color = y->color;
            x = y->right;
            if (y->parent == node) {
                x->parent = y;
            } else {
                _transplant(y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }
            _transplant(node, y);
            y->left = node->left;
            y->left->parent = y;
            y->color = node->color;
        }
        _node_allocator.destroy(node);
        _node_allocator.deallocate(node, 1);
        if (old_color == black) {
            _balance_tree_remove(x);
        }
        _update_nil_remove();
        --_size;
        return true;
    }

 private:
    struct compare_functions {

        compare_functions(const key_compare& _comp) : comp(_comp),
                                                      less(_comp),
                                                      not_less(_comp),
                                                      greater(_comp) {}

        compare_functions(const compare_functions& src) : comp(src.comp),
                                                          less(src.comp),
                                                          not_less(src.comp),
                                                          greater(src.comp) {}

        struct s_greater {
            key_compare comp;

            s_greater(const key_compare& _comp) : comp(_comp) {}

            bool operator()(const_reference x, const_reference y) const {
                return comp(y, x);
            }
        };

        struct s_not_less {
            key_compare comp;

            s_not_less(const key_compare& _comp) : comp(_comp) {}

            bool operator()(const_reference x, const_reference y) const {
                return !comp(x, y);
            }
        };

        struct s_less {
            key_compare comp;

            s_less(const key_compare& _comp) : comp(_comp) {}

            bool operator()(const_reference x, const_reference y) const {
                return comp(x, y);
            }
        };

        key_compare comp;
        s_not_less  not_less;
        s_greater   greater;
        s_less      less;
    };

    node_pointer        _root;
    node_pointer        _nil;
    size_type           _size;
    node_allocator      _node_allocator;
    compare_functions   _comp;

    node_pointer _create_new_node(const_reference data, node_pointer parent) {
        node_pointer        node = _node_allocator.allocate(1);

        _node_allocator.construct(node, node_base(data, parent, _nil, red));
        ++_size;
        return node;
    }

    void    _balance_tree_insert(node_pointer node) {
        node_pointer    sibling;
        bool            node_is_left_child;
        bool            parent_is_left_child;

		while (node != _root && node->parent->color == red) {
            sibling = _get_sibling(node->parent);
            if (sibling->color == red) {
                sibling->color = black;
                node->parent->color = black;
                node->parent->parent->color = red;
                node = node->parent->parent;
            } else {
                node_is_left_child = _is_left_child(node);
                parent_is_left_child = _is_left_child(node->parent);
                if (node_is_left_child != parent_is_left_child) {
                    node = node->parent;
                    if (node_is_left_child) {
                        _right_rotate(node);
                    } else {
                        _left_rotate(node);
                    }
                }
                node->parent->color = black;
                node->parent->parent->color = red;
                if (parent_is_left_child) {
                    _right_rotate(node->parent->parent);
                } else {
                    _left_rotate(node->parent->parent);
                }
            }
		}
		_root->color = black;
    }

    void    _balance_tree_remove(node_pointer node) {
        node_pointer            sibling;
        bool                    node_is_left_child;
        childrenCombinations    combination;

		while (node != _root && node->color == black) {
            sibling = _get_sibling(node);
            node_is_left_child = _is_left_child(node);
            if (sibling->color == red) {
                sibling->color = black;
                node->parent->color = red;
                if (node_is_left_child) {
                    _left_rotate(node->parent);
                    sibling = node->parent->right;
                } else {
					_right_rotate(node->parent);
					sibling = node->parent->left;
                }
            }
            combination = _get_children_combination(sibling);
            if (combination == bb) {
                sibling->color = red;
                node = node->parent;
            } else {
                if (node_is_left_child) {
                    if (combination == rb) {
                        sibling->left->color = black;
                        sibling->color = red;
                        _right_rotate(sibling);
                        sibling = node->parent->right;
                    } 
                    sibling->color = node->parent->color;
                    node->parent->color = black;
                    sibling->right->color = black;
                    _left_rotate(node->parent);
                } else {
                    if (combination == br) {
                        sibling->right->color = black;
                        sibling->color = red;
                        _left_rotate(sibling);
                        sibling = node->parent->left;
                    } 
                    sibling->color = node->parent->color;
                    node->parent->color = black;
                    sibling->left->color = black;
                    _right_rotate(node->parent);
                }
                node = _root;
            }
		}
		node->color = black;
    }

    bool _is_left_child(node_pointer node) {
        return node == node->parent->left;
    }

    node_pointer _get_sibling(node_pointer node) {
        return _is_left_child(node) ? node->parent->right : node->parent->left;
    }

    childrenCombinations    _get_children_combination(node_pointer node) {
        if (node->left->color == black) {
            return node->right->color == black ? bb : br;
        }
        return node->right->color == black ? rb : rr;
    }

    void _left_rotate(node_pointer x) {
        node_pointer y = x->right;

        x->right = y->left;
        if (y->left != _nil) {
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

    void _right_rotate(node_pointer x) {
        node_pointer y = x->left;

        x->left = y->right;
        if (y->right != _nil) {
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

    void _transplant(node_pointer node, node_pointer replacement) {
        if (node->parent == 0) {
            _root = replacement;
        } else if (node == node->parent->left) {
            node->parent->left = replacement;
        } else {
            node->parent->right = replacement;
        }
        replacement->parent = node->parent;
    }

    void _clear_recursive(node_pointer node) {
        if (node != _nil) {
            _clear_recursive(node->left);
            _clear_recursive(node->right);
            _node_allocator.destroy(node);
            _node_allocator.deallocate(node, 1);
        }
        _root = _nil;
    }

    template <typename function>
    node_pointer _find_bound(const_reference to_compare, function& condition) {
        node_pointer    x = _root;
        node_pointer    last_occurency = _nil;

        while (x != _nil) {
            if (condition(x->data, to_compare)) {
                last_occurency = x;
                x = x->left;
            } else {
                x = x->right;
            }
        }
        return last_occurency;
    }

    void    _update_nil_insert(node_pointer node) {
        if (!_nil->parent || _comp.less(_nil->parent->data, node->data)) {
            _nil->parent = node;
        }
    }

    void    _update_nil_remove(void) {
        _nil->parent = node_base::maximum(_root);
    }

    bool    _is_nil(node_pointer node) {
        return !node || node == _nil;
    }
};

}  /* namespace ft */

#endif   /* RBTREE_RBTREE_HPP_ */
