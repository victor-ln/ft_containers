/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TESTS_INCLUDES_MAP_TESTS_HPP_
#define TESTS_INCLUDES_MAP_TESTS_HPP_

#include <map>

#include "./utils.hpp"

#if STD == 1
    namespace ft = std;
#else
    #include "../../containers/map.hpp"
#endif

typedef std::map<int, int>::iterator                  stdIterator;
typedef ft::map<int, int>::iterator                   ftIterator;
typedef std::map<int, int>::const_iterator            stdConstIterator;
typedef ft::map<int, int>::const_iterator             ftConstIterator;

typedef std::map<int, int>::reverse_iterator          stdReverseIterator;
typedef ft::map<int, int>::reverse_iterator           ftReverseIterator;
typedef std::map<int, int>::const_reverse_iterator    stdConstReverseIterator;
typedef ft::map<int, int>::const_reverse_iterator     ftConstReverseIterator;

#endif  /* TESTS_INCLUDES_MAP_TESTS_HPP_ */
