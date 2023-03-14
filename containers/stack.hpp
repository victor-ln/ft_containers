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

    template <class Type, class Cont>
    friend bool operator==(const stack<Type, Cont>&, const stack<Type, Cont>&);

    template <class Type, class Cont>
    friend bool operator< (const stack<Type, Cont>&, const stack<Type, Cont>&);

    explicit stack(const Container& ctnr = Container()) : c(ctnr) {}
    ~stack() {}

    stack&          operator=(const stack& src) { c = src.c; return *this; }

    /*                              Capacity:                             */

    bool            empty(void) const { return c.empty(); }
    size_type       size(void) const { return c.size(); }

    /*                          Element access:                           */

    reference       top(void) { return c.back(); }
    const_reference top(void) const { return c.back(); }

    /*                              Modifiers:                            */

    void            push(const value_type& x) { c.push_back(x); }
    void            pop(void) { c.pop_back(); }

 protected:
    Container       c;
}; /* class stack */

template <class T, class Container>
bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return lhs.c == rhs.c;
}

template <class T, class Container>
bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return !(lhs == rhs);
}

template <class T, class Container>
bool operator< (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return lhs.c < rhs.c;
}

template <class T, class Container>
bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return !(rhs < lhs);
}

template <class T, class Container>
bool operator> (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return rhs < lhs;
}

template <class T, class Container>
bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return !(lhs < rhs);
}

/*                          Relational Operators                      */

} /* namespace ft */

#endif /* CONTAINERS_STACK_HPP_ */
