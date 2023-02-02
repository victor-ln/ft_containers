/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#pragma once
#ifndef FT_CONTAINERS_ITERATORS_ITERATORS_HPP_
#define FT_CONTAINERS_ITERATORS_ITERATORS_HPP_

#include <memory>
#include "./iterator_traits.hpp"

namespace ft {

template <typename T>
class reverse_iterator : ft::iterator<ft::iterator_traits<T>::iterator_category,
 ft::iterator_traits<T>::value_type,
 ft::iterator_traits<T>::difference_type,
 ft::iterator_traits<T>::pointer,
 ft::iterator_traits<T>::reference> {
 protected:
    T       current;

 public:
    reverse_iterator(void) : current() {}
    explicit reverse_iterator(iterator_type x) : current(x) {}
    template< class U >
    reverse_iterator(const reverse_iterator<U>& x) : current(x.current) {}
    ~reverse_iterator(void) {}

    /*                   Assignment operator                    */
    reverse_iterator&   operator=(const reverse_iterator& rhs) {
        current = rhs.current;
        return *this;
    }

    /*                   Accessors operators                    */
    reference   operator*(void) {
        T tmp = current;
        return *--tmp;
    }
    pointer     operator->(void) {
        return &this->operator*();
    }
    iterator_type base() const {
        return current;
    }
    reference   operator[](difference_type n) const {
        return *(*this + n);
    }

    /*                   Increment operators                    */
    reverse_iterator&   operator++(void) {
        --current;
        return *this;
    }
    reverse_iterator    operator++(int) {
        reverse_iterator    tmp(current);
        --current;
        return tmp;
    }
    reverse_iterator operator+(difference_type n) const {
        return reverse_iterator(current - n);
    }

    reverse_iterator& operator+=(difference_type n) {
        current -= n;
        return *this;
    }

    /*                   Decrement operators                    */
    reverse_iterator&   operator--(void) {
        ++current;
        return *this;
    }
    reverse_iterator    operator--(int) {
        reverse_iterator    tmp(current);
        ++current;
        return tmp;
    }
    reverse_iterator operator-(difference_type n) const {
        return reverse_iterator(current + n);
    }

    reverse_iterator& operator-=(difference_type n) {
        current += n;
        return *this;
    }
};
    /******************** Non-member function overloads ***********************/

    /*                   Relational operators                   */
    template< class Iterator1, class Iterator2 >
    bool operator==(const std::reverse_iterator<Iterator1>& lhs,
                    const std::reverse_iterator<Iterator2>& rhs) {
        return (lhs.base() == rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator!=(const std::reverse_iterator<Iterator1>& lhs,
                    const std::reverse_iterator<Iterator2>& rhs) {
        return (lhs.base() != rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator<(const std::reverse_iterator<Iterator1>& lhs,
                    const std::reverse_iterator<Iterator2>& rhs) {
        return (lhs.base() < rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator<=(const std::reverse_iterator<Iterator1>& lhs,
                    const std::reverse_iterator<Iterator2>& rhs) {
        return (lhs.base() <= rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator>(const std::reverse_iterator<Iterator1>& lhs,
                    const std::reverse_iterator<Iterator2>& rhs) {
        return (lhs.base() > rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator>=(const std::reverse_iterator<Iterator1>& lhs,
                    const std::reverse_iterator<Iterator2>& rhs) {
        return (lhs.base() >= rhs.base());
    }

    /*                   Increment operator                    */
    template< class T >
    reverse_iterator<T>  operator+(
        typename reverse_iterator<T>::difference_type n,
        const reverse_iterator<T>& it) {
        return reverse_iterator<T>(it.base() - n)
    }

    /*                   Decrement operators                    */
    template< class Iterator1, class Iterator2 >
    typename reverse_iterator<Iterator1>::difference_type   operator-(
        const reverse_iterator<Iterator1>& lhs,
        const reverse_iterator<Iterator2>& rhs) {
        return rhs.base() - lhs.base();
    }

}   /* namespace ft */

#endif /* FT_CONTAINERS_INCLUDES_FT_CONTAINERS_HPP_ */
