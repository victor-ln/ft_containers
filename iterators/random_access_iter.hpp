/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef ITERATORS_RANDOM_ACCESS_ITER_HPP_
#define ITERATORS_RANDOM_ACCESS_ITER_HPP_

#include "./iterator_traits.hpp"

namespace ft {

template <typename Tp>
class random_access_iter : iterator<std::random_access_iterator_tag, Tp> {
 protected:
    Tp       current;

    typedef ft::iterator_traits<Tp>                 _iter_traits;
 public:
    typedef Tp iterator_type;
    typedef typename _iter_traits::iterator_category iterator_category;
    typedef typename _iter_traits::value_type        value_type;
    typedef typename _iter_traits::difference_type   difference_type;
    typedef typename _iter_traits::reference         reference;
    typedef typename _iter_traits::pointer           pointer;

    random_access_iter(void) : current(NULL) {}
    explicit random_access_iter(const Tp& x) : current(x) {}
    random_access_iter(const random_access_iter& x) : current(x.base()) {}
    template <typename T>
    random_access_iter(const random_access_iter<T>& x) : current(x.base()) {}
    ~random_access_iter(void) {}

    /*                   Assignment operator                    */
    random_access_iter&   operator=(const random_access_iter& rhs) {
        current = rhs.base();
        return *this;
    }

    /*                   Accessors operators                    */
    reference   operator*(void) {
        return *current;
    }
    pointer     operator->(void) {
        return current;
    }
    const Tp& base() const {
        return current;
    }

    reference   operator[](difference_type n) const {
        return current[n];
    }

    /*                   Increment operators                    */
    random_access_iter&   operator++(void) {
        ++current;
        return *this;
    }
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
    random_access_iter&   operator--(void) {
        --current;
        return *this;
    }
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
};
    /******************** Non-member function overloads ***********************/

    /*                   Relational operators                   */
    template< class Iterator1, class Iterator2 >
    bool operator==(const random_access_iter<Iterator1>& lhs,
                    const random_access_iter<Iterator2>& rhs) {
        return (lhs.base() == rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator!=(const random_access_iter<Iterator1>& lhs,
                    const random_access_iter<Iterator2>& rhs) {
        return (lhs.base() != rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator<(const random_access_iter<Iterator1>& lhs,
                    const random_access_iter<Iterator2>& rhs) {
        return (lhs.base() < rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator<=(const random_access_iter<Iterator1>& lhs,
                    const random_access_iter<Iterator2>& rhs) {
        return (lhs.base() <= rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator>(const random_access_iter<Iterator1>& lhs,
                    const random_access_iter<Iterator2>& rhs) {
        return (lhs.base() > rhs.base());
    }
    template< class Iterator1, class Iterator2 >
    bool operator>=(const random_access_iter<Iterator1>& lhs,
                    const random_access_iter<Iterator2>& rhs) {
        return (lhs.base() >= rhs.base());
    }

    /*                   Increment operator                    */
    template<class T>
    random_access_iter<T>  operator+(
        typename random_access_iter<T>::difference_type n,
        const random_access_iter<T>& it) {
        return random_access_iter<T>(it.base() + n);
    }

    /*                   Decrement operators                    */
    template<class Iterator1, class Iterator2>
    typename random_access_iter<Iterator1>::difference_type   operator-(
        const random_access_iter<Iterator1>& lhs,
        const random_access_iter<Iterator2>& rhs) {
        return lhs.base() - rhs.base();
    }
}   /* namespace ft */

#endif /* ITERATORS_RANDOM_ACCESS_ITER_HPP_ */
