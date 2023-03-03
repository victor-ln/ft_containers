/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef ITERATORS_REVERSE_ITER_HPP_
#define ITERATORS_REVERSE_ITER_HPP_

#include "./iterator_traits.hpp"

namespace ft {

template <typename T>
class reverse_iter {
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

    reverse_iter() : current(0) {}

    explicit reverse_iter(const T& x) : current(x) {}

    reverse_iter(const reverse_iter& x) : current(x.base()) {}

    template<typename U>
    reverse_iter(const reverse_iter<U>& x) : current(x.base()) {}

    ~reverse_iter() {}

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

};  /* class reverse_iter */

/*                   Relational operators                   */

template<class T1, class T2>
bool operator==(const reverse_iter<T1>& lhs, const reverse_iter<T2>& rhs) {
    return (lhs.base() == rhs.base());
}
template<class T1, class T2>
bool operator!=(const reverse_iter<T1>& lhs, const reverse_iter<T2>& rhs) {
    return (lhs.base() != rhs.base());
}
template<class T1, class T2>
bool operator<(const reverse_iter<T1>& lhs, const reverse_iter<T2>& rhs) {
    return (rhs.base() < lhs.base());
}
template<class T1, class T2>
bool operator<=(const reverse_iter<T1>& lhs, const reverse_iter<T2>& rhs) {
    return (rhs.base() <= lhs.base());
}
template<class T1, class T2>
bool operator>(const reverse_iter<T1>& lhs, const reverse_iter<T2>& rhs) {
    return (rhs.base() > lhs.base());
}
template<class T1, class T2>
bool operator>=(const reverse_iter<T1>& lhs, const reverse_iter<T2>& rhs) {
    return (rhs.base() >= lhs.base());
}

/*                   Increment operator                     */

template<class T>
reverse_iter<T> operator+(typename reverse_iter<T>::difference_type n,
                          const reverse_iter<T>& it) {
    return reverse_iter<T>(it.base() - n);
}

/*                   Decrement operators                    */

template<class T1, class T2>
typename reverse_iter<T1>::difference_type
        operator-(const reverse_iter<T1>& lhs, const reverse_iter<T2>& rhs) {
    return rhs.base() - lhs.base();
}

}   /* namespace ft */

#endif /* ITERATORS_REVERSE_ITER_HPP_ */
