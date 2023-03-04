/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef ITERATORS_RB_TREE_ITER_HPP_
#define ITERATORS_RB_TREE_ITER_HPP_

#include "./iterator_traits.hpp"

namespace ft {

template <typename T>
class rb_tree_iter {
 protected:
    using typename node<value_type>::nodePtr;
    nodePtr       current;

    typedef ft::iterator_traits<T>                      _iter_traits;
 public:
    typedef T                                           iterator_type;
    typedef std::bidirectional_iterator_tag             iterator_category;
    typedef typename _iter_traits::value_type           value_type;
    typedef typename _iter_traits::difference_type      difference_type;
    typedef typename _iter_traits::reference            reference;
    typedef typename _iter_traits::pointer              pointer;

    rb_tree_iter() : current(0) {}

    explicit rb_tree_iter(const T& x) : current(x) {}

    rb_tree_iter(const rb_tree_iter& x) : current(x.base()) {}

    template <typename U>
    rb_tree_iter(const rb_tree_iter<U>& x) : current(x.base()) {}

    ~rb_tree_iter() {}

    /*                   Assignment operator                    */

    rb_tree_iter&   operator=(const rb_tree_iter& rhs) {
        current = rhs.base();
        return *this;
    }

    /*                   Accessors operators                    */

    reference   operator*(void) const { return current->data; }
    pointer     operator->(void) const { return &operator*(); }
    const T&    base(void) const { return current; }

    /*                   Increment operators                    */

    rb_tree_iter&   operator++(void) {
         current = current->successor() ; return *this;
    }
    rb_tree_iter    operator++(int) {
        rb_tree_iter    tmp(current);
        current = current->successor();
        return tmp;
    }

    /*                   Decrement operators                    */

    rb_tree_iter&   operator--(void) {
        current = current->predecessor(); return *this;
    }
    rb_tree_iter    operator--(int) {
        rb_tree_iter    tmp(current);
        current = current->predecessor();
        return tmp;
    }

    bool operator==(const rb_tree_iter& rhs) {
        return current == rhs.current;
    }

    bool operator!=(const rb_tree_iter& rhs) {
        return current != rhs.current;
    }
};

}

#endif  /* ITERATORS_RB_TREE_ITER_HPP_ */
