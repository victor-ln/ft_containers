/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TESTS_INCLUDES_VECTOR_TESTS_HPP_
#define TESTS_INCLUDES_VECTOR_TESTS_HPP_

#include <vector>

#include "./utils.hpp"

#if STD == 1
    namespace ft = std;
#else
    #include "../../containers/vector.hpp"
#endif

typedef std::vector<int>::iterator                  stdIterator;
typedef ft::vector<int>::iterator                   ftIterator;
typedef std::vector<int>::const_iterator            stdConstIterator;
typedef ft::vector<int>::const_iterator             ftConstIterator;

typedef std::vector<int>::reverse_iterator          stdReverseIterator;
typedef ft::vector<int>::reverse_iterator           ftReverseIterator;
typedef std::vector<int>::const_reverse_iterator    stdConstReverseIterator;
typedef ft::vector<int>::const_reverse_iterator     ftConstReverseIterator;

#endif  /* TESTS_INCLUDES_VECTOR_TESTS_HPP_ */
