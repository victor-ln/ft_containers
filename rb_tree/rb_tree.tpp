/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "rb_tree.hpp"

namespace ft {

    template <RBTREE_TEMPLATE>
    RBTREE_CLASS::rb_tree(const value_type& val) {
      _root = _rootBase = _allocator.allocate(1);
      _root->color = black;
      _root->left = 0;
      _root->right = 0;
      _root->data = val;
    }

} // namespace ft
