/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef ITERATORS_REVERSE_ITER_HPP_
#define ITERATORS_REVERSE_ITER_HPP_

#include "./iterator_traits.hpp"

namespace ft {

template <typename T>
class reverse_iter
      : public ft::iterator<typename ft::iterator_traits<T>::iterator_category,
                        typename ft::iterator_traits<T>::value_type,
                        typename ft::iterator_traits<T>::difference_type,
                        typename ft::iterator_traits<T>::pointer,
                        typename ft::iterator_traits<T>::reference> {
 protected:
    T       current;

 public:
    typedef T                                                   iterator_type;
    typedef typename ft::iterator_traits<T>::difference_type    difference_type;
    typedef typename ft::iterator_traits<T>::reference          reference;
    typedef typename ft::iterator_traits<T>::pointer            pointer;

    reverse_iter(void) : current() {}
    explicit reverse_iter(iterator_type x) : current(x) {}
    template< class U >
    reverse_iter(const reverse_iter<U>& x) : current(x.base()) {}
    ~reverse_iter(void) {}

    /*                   Assignment operator                    */
    reverse_iter&   operator=(const reverse_iter& rhs) {
        current = rhs.current;
        return *this;
    }

    /*                   Accessors operators                    */
    reference   operator*(void) const {
        T tmp = current;
        return *--tmp;
    }
    pointer     operator->(void) const {
        return &operator*();
    }
    iterator_type base(void) const {
        return current;
    }
    reference   operator[](difference_type n) const {
        return *(*this + n);
    }

    /*                   Increment operators                    */
    reverse_iter&   operator++(void) {
        --current;
        return *this;
    }
    reverse_iter    operator++(int) {
        reverse_iter    tmp(current);
        --current;
        return tmp;
    }
    reverse_iter operator+(difference_type n) const {
        return reverse_iter(current - n);
    }

    reverse_iter& operator+=(difference_type n) {
        current -= n;
        return *this;
    }

    /*                   Decrement operators                    */
    reverse_iter&   operator--(void) {
        ++current;
        return *this;
    }
    reverse_iter    operator--(int) {
        reverse_iter    tmp(current);
        ++current;
        return tmp;
    }
    reverse_iter operator-(difference_type n) const {
        return reverse_iter(current + n);
    }

    reverse_iter& operator-=(difference_type n) {
        current += n;
        return *this;
    }
};
    /******************** Non-member function overloads ***********************/

    /*                   Relational operators                   */
    template< class Iterator1, class Iterator2 >
    bool operator==(const reverse_iter<Iterator1>& lhs,
                    const reverse_iter<Iterator2>& rhs) {
        return (lhs.base() == rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator!=(const reverse_iter<Iterator1>& lhs,
                    const reverse_iter<Iterator2>& rhs) {
        return (lhs.base() != rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator<(const reverse_iter<Iterator1>& lhs,
                    const reverse_iter<Iterator2>& rhs) {
        return (rhs.base() < lhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator<=(const reverse_iter<Iterator1>& lhs,
                    const reverse_iter<Iterator2>& rhs) {
        return (rhs.base() <= lhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator>(const reverse_iter<Iterator1>& lhs,
                    const reverse_iter<Iterator2>& rhs) {
        return (rhs.base() > lhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator>=(const reverse_iter<Iterator1>& lhs,
                    const reverse_iter<Iterator2>& rhs) {
        return (rhs.base() >= lhs.base());
    }

    /*                   Increment operator                    */
    template<class T>
    reverse_iter<T>  operator+(
        typename reverse_iter<T>::difference_type n,
        const reverse_iter<T>& it) {
        return reverse_iter<T>(it.base() - n);
    }

    /*                   Decrement operators                    */
    template<class Iterator1, class Iterator2>
    typename reverse_iter<Iterator1>::difference_type   operator-(
        const reverse_iter<Iterator1>& lhs,
        const reverse_iter<Iterator2>& rhs) {
        return rhs.base() - lhs.base();
    }

}   /* namespace ft */

#endif /* ITERATORS_REVERSE_ITER_HPP_ */
