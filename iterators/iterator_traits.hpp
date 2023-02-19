/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef ITERATORS_ITERATOR_TRAITS_HPP_
#define ITERATORS_ITERATOR_TRAITS_HPP_

#include <cstddef>

namespace ft {

template<typename Category, typename Tp, typename Distance = std::ptrdiff_t,
 typename Pointer = Tp*, typename Reference = Tp&>
struct iterator {
    typedef Category                                   iterator_category;
    typedef Tp                                         value_type;
    typedef Distance                                   difference_type;
    typedef Pointer                                    pointer;
    typedef Reference                                  reference;
};

template<class Iter>
struct iterator_traits {
    typedef typename Iter::iterator_category            iterator_category;
    typedef typename Iter::value_type                   value_type;
    typedef typename Iter::difference_type              difference_type;
    typedef typename Iter::pointer                      pointer;
    typedef typename Iter::reference                    reference;
};

template<class T>
struct iterator_traits<T*> {
    typedef std::ptrdiff_t                              difference_type;
    typedef T                                           value_type;
    typedef T*                                          pointer;
    typedef T&                                          reference;
    typedef std::random_access_iterator_tag             iterator_category;
};

template<class T>
struct iterator_traits<const T*> {
    typedef std::ptrdiff_t                              difference_type;
    typedef T                                           value_type;
    typedef const T*                                    pointer;
    typedef const T&                                    reference;
    typedef std::random_access_iterator_tag             iterator_category;
};

}  /* namespace ft */

#endif /* ITERATORS_ITERATOR_TRAITS_HPP_ */
