/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TESTS_INCLUDES_SET_TESTS_HPP_
#define TESTS_INCLUDES_SET_TESTS_HPP_

#include <set>

#include "./utils.hpp"

#if STD == 1
    namespace ft = std;
#else
    #include "../../containers/set.hpp"

    typedef std::set<int>::iterator                 t_stdIterator;
    typedef std::set<int>::const_iterator           t_stdConstIterator;
    typedef std::set<int>::reverse_iterator         t_stdReverseIterator;
    typedef std::set<int>::const_reverse_iterator   t_stdConstReverseIterator;

#endif

typedef ft::set<int>::iterator                      t_ftIterator;
typedef ft::set<int>::const_iterator                t_ftConstIterator;
typedef ft::set<int>::reverse_iterator              t_ftReverseIterator;
typedef ft::set<int>::const_reverse_iterator        t_ftConstReverseIterator;

typedef ft::pair<t_ftIterator, bool>                t_ftPairReturn;

template <typename T>
bool compare(T x, T y) {
    return x == y;
}

template <typename T>
void print(T x) {
    std::cout << x << ' ';
}

#endif  /* TESTS_INCLUDES_SET_TESTS_HPP_ */
