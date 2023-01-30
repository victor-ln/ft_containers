/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "./stack.hpp"

namespace ft {
    template <class T, class Container >
    stack<T, Container>::stack(const Container& ctnr) : _c(ctnr) {}

    template <class T, class Container >
    stack<T, Container>::~stack() {}

    template <class T, class Container >
    stack<T, Container>& stack<T, Container>::operator=(const stack& rhs) {
        _c = rhs._c;
        return *this;
    }

    template <class T, class Container >
    bool    stack<T, Container>::empty(void) const {
        return _c.empty();
    }

    template <class T, class Container >
    typename stack<T, Container>::size_type
        stack<T, Container>::size(void) const {
        return _c.size();
    }

    template <class T, class Container >
    typename stack<T, Container>::reference  stack<T, Container>::top(void) {
        return _c.back();
    }

    template <class T, class Container >
    typename stack<T, Container>::const_reference
        stack<T, Container>::top(void) const {
        return _c.back();
    }

    template <class T, class Container >
    void    stack<T, Container>::push(const value_type& x) {
        _c.push_back(x);
    }

    template <class T, class Container >
    void    stack<T, Container>::pop(void) {
        _c.pop_back();
    }

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
}  // namespace ft
