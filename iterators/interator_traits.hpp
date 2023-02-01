/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#pragma once
#ifndef FT_CONTAINERS_INCLUDES_FT_CONTAINERS_ITERATOR_TRAITS_HPP_
#define FT_CONTAINERS_INCLUDES_FT_CONTAINERS_ITERATOR_TRAITS_HPP_

#include <cstddef>

namespace ft {

template<typename _Category, typename _Tp, typename _Distance = std::ptrdiff_t,
 typename _Pointer = _Tp*, typename _Reference = _Tp&>
struct iterator {
    typedef _Category                                   iterator_category;
    typedef _Tp                                         value_type;
    typedef _Distance                                   difference_type;
    typedef _Pointer                                    pointer;
    typedef _Reference                                  reference;
};  /* struct iterator */

template<class Iter>
struct iterator_traits {
    typedef typename Iter::iterator_category            iterator_category;
    typedef typename Iter::value_type                   value_type;
    typedef typename Iter::difference_type              difference_type;
    typedef difference_type                             distance_type;
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

};  /* namespace ft */

#endif /* FT_CONTAINERS_INCLUDES_FT_CONTAINERS_ITERATOR_TRAITS_HPP_ */
