/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TESTS_INCLUDES_SET_TESTS_HPP_
#define TESTS_INCLUDES_SET_TESTS_HPP_

#include <set>

#include "./utils.hpp"

#if STD == 1
    namespace ft = std;
#else
    #include "../../containers/set.hpp"
#endif

typedef std::set<int>::iterator                  stdIterator;
typedef ft::set<int>::iterator                   ftIterator;
typedef std::set<int>::const_iterator            stdConstIterator;
typedef ft::set<int>::const_iterator             ftConstIterator;

typedef std::set<int>::reverse_iterator          stdReverseIterator;
typedef ft::set<int>::reverse_iterator           ftReverseIterator;
typedef std::set<int>::const_reverse_iterator    stdConstReverseIterator;
typedef ft::set<int>::const_reverse_iterator     ftConstReverseIterator;

#endif  /* TESTS_INCLUDES_SET_TESTS_HPP_ */
