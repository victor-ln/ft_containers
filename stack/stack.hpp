/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef FT_CONTAINERS_INCLUDES_FT_CONTAINERS_STACK_HPP_
#define FT_CONTAINERS_INCLUDES_FT_CONTAINERS_STACK_HPP_

#include <memory>

#include "../vector/vector.hpp"

namespace ft {
template <class T, class Container = vector<T> >
class stack {
 public:
    typedef Container                                   container_type;
    typedef typename Container::value_type              value_type;
    typedef typename Container::size_type               size_type;
    typedef typename Container::reference               reference;
    typedef typename Container::const_reference         const_reference;

    explicit stack(const Container& ctnr = Container());
    ~stack();

    stack&              operator=(const stack&);

    /*                              Capacity:                             */
    bool                empty(void) const;
    size_type           size(void) const;

    /*                          Element access:                           */
    reference           top(void);
    const_reference     top(void) const;

    /*                              Modifiers:                            */
    void                push(const value_type&);
    void                pop(void);

 protected:
    Container           _c;
};
    /*                          Non member functions                          */

    template <class T, class Alloc>
    bool operator==(const stack<T, Alloc>& lhs, const stack<T, Alloc>& rhs);
    template <class T, class Alloc>
    bool operator!=(const stack<T, Alloc>& lhs, const stack<T, Alloc>& rhs);
    template <class T, class Alloc>
    bool operator< (const stack<T, Alloc>& lhs, const stack<T, Alloc>& rhs);
    template <class T, class Alloc>
    bool operator<=(const stack<T, Alloc>& lhs, const stack<T, Alloc>& rhs);
    template <class T, class Alloc>
    bool operator> (const stack<T, Alloc>& lhs, const stack<T, Alloc>& rhs);
    template <class T, class Alloc>
    bool operator>=(const stack<T, Alloc>& lhs, const stack<T, Alloc>& rhs);
};  // namespace ft

#include "./stack.tpp"

#endif /* FT_CONTAINERS_INCLUDES_FT_CONTAINERS_STACK_HPP_ */
