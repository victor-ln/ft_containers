/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef RBTREE_TREE_NODE_HPP_
#define RBTREE_TREE_NODE_HPP_

#include "enums.hpp"

namespace ft {

template <typename T>
struct node {
    typedef node*       node_pointer;
    T               data;
    node_pointer    left;
    node_pointer    right;
    node_pointer    parent;
    node_pointer    leaf;
    nodeColor       color;

    node(const T&       _data = T(),
         node_pointer   _parent = 0,
         node_pointer   _leaf = 0,
         nodeColor      _color = black)
                    :   data(_data),
                        left(_leaf),
                        right(_leaf),
                        parent(_parent),
                        leaf(_leaf),
                        color(_color) {}

    static node_pointer minimum(node_pointer node) {
        while (node->left != node->leaf) {
            node = node->left;
        }
        return node;
    }

    static node_pointer maximum(node_pointer node) {
        while (node->right != node->leaf) {
            node = node->right;
        }
        return node;
    }

    static node_pointer successor(node_pointer x) {
        if (x->right != x->leaf) {
            return minimum(x->right);
        }
        if (x->_is_last_node()) {
            return x->leaf;
        }
        node_pointer y = x->parent;
        while (y != y->leaf && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    static node_pointer predecessor(node_pointer x) {
        if (x->left != x->leaf) {
            return maximum(x->left);
        }
        if (x->parent->_is_last_node()) {
            return x->parent;
        }
        node_pointer y = x->parent;
        while (y != y->leaf && x == y->left) {
            x = y;
            y = y->parent;
        }
        return y;
    }

 private:
    bool _is_last_node(void) {
        return this->leaf->parent == this;
    }
};  /* struct node */

}   /* namespace ft */

#endif  /* RBTREE_TREE_NODE_HPP_ */
