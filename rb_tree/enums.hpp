/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef RB_TREE_ENUMS_HPP_
#define RB_TREE_ENUMS_HPP_

namespace ft {

enum nodeColor {
    black = false,
    red = true
};

enum childrenCombinations {
    bb,
    br,
    rr,
    rb
};

}   /* namespace ft */

#endif  /* RB_TREE_ENUMS_HPP_ */
