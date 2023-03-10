/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef ITERATORS_RANDOM_ACCESS_ITER_HPP_
#define ITERATORS_RANDOM_ACCESS_ITER_HPP_

#include "./iterator_traits.hpp"

namespace ft {

template <typename T>
class random_access_iter {
 protected:
    T       current;

    typedef ft::iterator_traits<T>                      _iter_traits;

 public:
    typedef T                                           iterator_type;
    typedef typename _iter_traits::iterator_category    iterator_category;
    typedef typename _iter_traits::value_type           value_type;
    typedef typename _iter_traits::difference_type      difference_type;
    typedef typename _iter_traits::reference            reference;
    typedef typename _iter_traits::pointer              pointer;

    random_access_iter() : current() {}

    explicit random_access_iter(const T& x) : current(x) {}

    random_access_iter(const random_access_iter& x) : current(x.base()) {}

    template <typename U>
    random_access_iter(const random_access_iter<U>& x) : current(x.base()) {}

    ~random_access_iter() {}

    /*                   Assignment operator                    */

    random_access_iter&   operator=(const random_access_iter& rhs) {
        current = rhs.base();
        return *this;
    }

    /*                   Accessors operators                    */

    reference   operator*(void) const { return *current; }
    pointer     operator->(void) const { return current; }
    const T&    base(void) const { return current; }
    reference   operator[](difference_type n) const { return current[n]; }

    /*                   Increment operators                    */

    random_access_iter&   operator++(void) { ++current; return *this; }
    random_access_iter    operator++(int) {
        random_access_iter    tmp(current);
        ++current;
        return tmp;
    }
    random_access_iter operator+(difference_type n) const {
        return random_access_iter(current + n);
    }

    random_access_iter& operator+=(difference_type n) {
        current += n;
        return *this;
    }

    /*                   Decrement operators                    */

    random_access_iter&   operator--(void) { --current; return *this; }
    random_access_iter    operator--(int) {
        random_access_iter    tmp(current);
        --current;
        return tmp;
    }
    random_access_iter operator-(difference_type n) const {
        return random_access_iter(current - n);
    }

    random_access_iter& operator-=(difference_type n) {
        current -= n;
        return *this;
    }
};  /* class random_access_iter */

/*                   Relational operators                   */

template<class T1, class T2>
bool operator==(const random_access_iter<T1>& lhs,
                const random_access_iter<T2>& rhs) {
    return (lhs.base() == rhs.base());
}
template<class T1, class T2>
bool operator!=(const random_access_iter<T1>& lhs,
                const random_access_iter<T2>& rhs) {
    return (lhs.base() != rhs.base());
}
template<class T1, class T2>
bool operator<(const random_access_iter<T1>& lhs,
               const random_access_iter<T2>& rhs) {
    return (lhs.base() < rhs.base());
}
template<class T1, class T2>
bool operator<=(const random_access_iter<T1>& lhs,
                const random_access_iter<T2>& rhs) {
    return (lhs.base() <= rhs.base());
}
template<class T1, class T2>
bool operator>(const random_access_iter<T1>& lhs,
               const random_access_iter<T2>& rhs) {
    return (lhs.base() > rhs.base());
}
template<class T1, class T2>
bool operator>=(const random_access_iter<T1>& lhs,
               const random_access_iter<T2>& rhs) {
    return (lhs.base() >= rhs.base());
}

/*                   Increment operator                     */

template<class T>
random_access_iter<T>  operator+(
    typename random_access_iter<T>::difference_type n,
    const random_access_iter<T>& it) {
    return random_access_iter<T>(it.base() + n);
}

/*                   Decrement operators                    */

template<class T1, class T2>
typename random_access_iter<T1>::difference_type   operator-(
    const random_access_iter<T1>& lhs,
    const random_access_iter<T2>& rhs) {
    return lhs.base() - rhs.base();
}
}   /* namespace ft */

#endif /* ITERATORS_RANDOM_ACCESS_ITER_HPP_ */
