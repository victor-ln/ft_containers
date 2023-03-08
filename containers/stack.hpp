/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef CONTAINERS_STACK_HPP_
#define CONTAINERS_STACK_HPP_

#include <memory>

#include "./vector.hpp"

namespace ft {

template <class T, class Container = vector<T> >
class stack {
 public:
    typedef Container                               container_type;
    typedef typename Container::value_type          value_type;
    typedef typename Container::size_type           size_type;
    typedef typename Container::reference           reference;
    typedef typename Container::const_reference     const_reference;

    explicit stack(const Container& ctnr) : _c(ctnr) {}
    ~stack() {}

    stack&          operator=(const stack& src) { _c = src._c; return *this; }

    /*                              Capacity:                             */

    bool            empty(void) const { return _c.empty(); }
    size_type       size(void) const { return _c.size(); }

    /*                          Element access:                           */

    reference       top(void) { return _c.back(); }
    const_reference top(void) const { return _c.back(); }

    /*                              Modifiers:                            */

    void            push(const value_type&) { _c.push_back(x); }
    void            pop(void) { _c.pop_back(); }

 protected:
    Container       _c;
}; /* class stack */

/*                          Relational Operators                      */

template <class T, class Alloc>
bool operator==(const stack<T, Alloc>& lhs, const stack<T, Alloc>& rhs) {
    return lhs._c == rhs._c;
}

template <class T, class Alloc>
bool operator!=(const stack<T, Alloc>& lhs, const stack<T, Alloc>& rhs) {
    return lhs._c != rhs._c;
}

template <class T, class Alloc>
bool operator< (const stack<T, Alloc>& lhs, const stack<T, Alloc>& rhs) {
    return lhs._c < rhs._c;
}

template <class T, class Alloc>
bool operator<=(const stack<T, Alloc>& lhs, const stack<T, Alloc>& rhs) {
    return lhs._c <= rhs._c;
}

template <class T, class Alloc>
bool operator> (const stack<T, Alloc>& lhs, const stack<T, Alloc>& rhs) {
    return lhs._c > rhs._c;
}

template <class T, class Alloc>
bool operator>=(const stack<T, Alloc>& lhs, const stack<T, Alloc>& rhs) {
    return lhs._c >= rhs._c;
}

}; /* namespace ft */

#endif /* CONTAINERS_STACK_HPP_ */
