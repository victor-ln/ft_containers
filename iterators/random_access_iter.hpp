/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef ITERATORS_RANDOM_ACCESS_ITER_HPP_
#define ITERATORS_RANDOM_ACCESS_ITER_HPP_

#include "./iterator_traits.hpp"

namespace ft {

template <typename Tp>
class random_access_iter : public iterator<random_access_iterator_tag, Tp> {
 protected:
    Tp       current;

    typedef iterator_traits<Tp>                          traits_type;

 public:
    typedef Tp                                           iterator_type;
    typedef typename traits_type::iterator_category      iterator_category;
    typedef typename traits_type::value_type             value_type;
    typedef typename traits_type::difference_type        difference_type;
    typedef typename traits_type::reference              reference;
    typedef typename traits_type::pointer                pointer;

    random_access_iter(void) : current() {}
    explicit random_access_iter(const Tp& x) : current(x) {}
    random_access_iter(const random_access_iter& x) : current(x.current) {}
    template <typename T>
    random_access_iter(const random_access_iter<T>& x) : current(x.current) {}
    ~random_access_iter(void) {}

    /*                   Assignment operator                    */
    random_access_iter&   operator=(const random_access_iter& rhs) {
        current = rhs.current;
        return *this;
    }

    /*                   Accessors operators                    */
    reference   operator*(void) {
        return *current;
    }
    pointer     operator->(void) {
        return current;
    }
    iterator_type base(void) const {
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
        return random_access_iter<T>(it.base() + n)
    }

    /*                   Decrement operators                    */
    template<class Iterator1, class Iterator2>
    typename random_access_iter<Iterator1>::difference_type   operator-(
        const random_access_iter<Iterator1>& lhs,
        const random_access_iter<Iterator2>& rhs) {
        return rhs.base() - lhs.base();
    }
}; /* namespace ft */

#endif /* ITERATORS_RANDOM_ACCESS_ITER_HPP_ */
