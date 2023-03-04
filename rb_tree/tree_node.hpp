/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef RBTREE_TREE_NODE_HPP_
#define RBTREE_TREE_NODE_HPP_

#include "enums.hpp"

namespace ft {

template <typename T>
struct node {
    typedef struct node<T>*     nodePtr;

    T*          data;
    nodePtr     left;
    nodePtr     right;
    nodePtr     parent;
    nodeColor   color;

    node() : data(0), left(0), right(0), parent(0), color(black) {}

    node(const T* new_data, nodeColor new_color)
        : data(new_data), left(0), right(0), parent(0), color(new_color) {}

    static nodePtr maximum(nodePtr node) {
        while (node->right->data) {
            node = node->right;
        }
        return node;
    }

    static nodePtr minimum(nodePtr node) {
        while (node->left->data) {
            node = node->left;
        }
        return node;
    }

    nodePtr successor(void) {
        if (right) {
            return minimum(right);
        }
        nodePtr x = this;
        while (x->parent && x == x->parent->right) {
            x = x->parent;
        }
        return x->parent;
    }

    nodePtr predecessor(void) {
        if (left) {
            return maximum(left);
        }
        nodePtr x = this;
        while (x->parent && x == x->parent->left) {
            x = x->parent;
        }
        return x->parent;
    }
};

}   /* namespace ft */

#endif  /* RBTREE_TREE_NODE_HPP_ */
