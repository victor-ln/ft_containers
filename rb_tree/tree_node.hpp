/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef RBTREE_TREE_NODE_HPP_
#define RBTREE_TREE_NODE_HPP_

namespace ft {

enum nodeColor { black, red };

template <typename Tp>
struct node {
    typedef struct node<Tp>*                               nodePtr;
    typedef const struct node<Tp>*                         constNodePtr;

    Tp        data;
    nodePtr   left;
    nodePtr   right;
    nodePtr   parent;
    nodeColor color;

    nodePtr maximum(nodePtr node) {
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    constNodePtr maximum(constNodePtr node) {
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    nodePtr minimum(nodePtr node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    constNodePtr minimum(constNodePtr node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }
};
    
} // namespace ft

#endif  // RBTREE_TREE_NODE_HPP_
