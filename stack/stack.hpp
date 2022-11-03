#pragma once
#ifndef FT_CONTAINERS_INCLUDES_FT_CONTAINERS_STACK_HPP_
#define FT_CONTAINERS_INCLUDES_FT_CONTAINERS_STACK_HPP_

#include <memory>

#include "../vector/vector.hpp"

namespace ft {
    template <class T, class Container = ft::vector<T> >
    class stack {
     public:
        typedef Container                                   container_type;
        typedef typename Container::value_type              value_type;
        typedef typename Container::allocator_type          AllocTp;
        typedef typename Container::size_type               size_type;
        typedef typename Container::difference_type         difference_type;
        typedef typename Container::reference               reference;
        typedef typename Container::const_reference         const_reference;
        typedef typename Container::pointer                 pointer;
        typedef typename Container::const_pointer           const_pointer;

        stack(void) {}
        stack(const stack&);
        ~stack(void) {}

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

        /*                              Allocator:                            */
        allocator_type      get_allocator(void) const;

     protected:
        Container           c;
    };
    /*                          Non member functions                          */

    /*                          Relational Operators                          */
    template <class T, class Alloc>
    bool operator==(const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs);
    template <class T, class Alloc>
    bool operator!=(const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs);
    template <class T, class Alloc>
    bool operator< (const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs);
    template <class T, class Alloc>
    bool operator<=(const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs);
    template <class T, class Alloc>
    bool operator> (const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs);
    template <class T, class Alloc>
    bool operator>=(const stack<T,Alloc>& lhs, const stack<T,Alloc>& rhs);
};


#endif /* FT_CONTAINERS_INCLUDES_FT_CONTAINERS_STACK_HPP_ */
