/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef ITERATORS_RB_TREE_ITER_HPP_
#define ITERATORS_RB_TREE_ITER_HPP_

#include "./iterator_traits.hpp"

namespace ft {

template <typename T>
class rb_tree_iter {
    typedef ft::iterator_traits<T>                      _iter_traits;

 public:
    typedef T                                           iterator_type;
    typedef std::bidirectional_iterator_tag             iterator_category;
    typedef typename _iter_traits::value_type           value_type;
    typedef typename _iter_traits::difference_type      difference_type;
    typedef typename _iter_traits::reference            reference;
    typedef typename _iter_traits::pointer              pointer;

 protected:
    typedef ft::node<value_type>                        node_base;
    typedef node_base*                                  node_pointer;
    typedef const node_base*                            const_node_pointer;

    node_pointer       _current;

 public:
    rb_tree_iter() : _current(0) {}

    explicit rb_tree_iter(node_pointer x) : _current(x) {}

    explicit rb_tree_iter(const_node_pointer x)
            : _current(const_cast<node_pointer>(x)) {}

    rb_tree_iter(const rb_tree_iter& x) : _current(x.base()) {}

    template <typename U>
    rb_tree_iter(const rb_tree_iter<U>& x) : _current(x.base()) {}

    ~rb_tree_iter() {}

    /*                   Assignment operator                    */

    rb_tree_iter&   operator=(const rb_tree_iter& rhs) {
        _current = rhs.base();
        return *this;
    }

    /*                   Accessors operators                    */

    reference   operator*(void) const { return _current->data; }
    pointer     operator->(void) const { return &_current->data; }
    node_pointer    base(void) { return _current; }
    const node_pointer    base(void) const { return _current; }

    /*                   Increment operators                    */

    rb_tree_iter&   operator++(void) {
         _current = node_base::successor(_current); return *this;
    }
    rb_tree_iter    operator++(int) {
        rb_tree_iter    tmp(_current);
        _current = node_base::successor(_current);
        return tmp;
    }

    /*                   Decrement operators                    */

    rb_tree_iter&   operator--(void) {
        _current = node_base::predecessor(_current); return *this;
    }
    rb_tree_iter    operator--(int) {
        rb_tree_iter    tmp(_current);
        _current = node_base::predecessor(_current);
        return tmp;
    }

    bool operator==(const rb_tree_iter& rhs) {
        return _current == rhs._current;
    }

    bool operator!=(const rb_tree_iter& rhs) {
        return _current != rhs._current;
    }
};  /* class rb_tree_iter */

}   /* namespace ft */

#endif  /* ITERATORS_RB_TREE_ITER_HPP_ */
