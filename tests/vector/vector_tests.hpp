/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TESTS_VECTOR_VECTOR_TESTS_HPP_
#define TESTS_VECTOR_VECTOR_TESTS_HPP_

#include <vector>

#include "../utils/utils.hpp"

#if STD == 1
    namespace ft = std;
#else
    #include "../../vector/vector.hpp"
    #include "../../algorithm/equal.hpp"
    #include "../../algorithm/lexicographical_compare.hpp"
#endif

#define EXCEPT_MSG_01 \
"Error: accessing out of range element didn't throw an exception\n"

#define EXCEPT_MSG_02 \
"resizing to a size greater than the maximum size didn't throw an exception\n"

#define EXCEPT_MSG_03 \
"Error: pushing back to a full vector didn't throw an exception\n"

#define EXCEPT_MSG_04 \
"Error: resizing to a negative size didn't throw an exception\n"

#define EXCEPT_MSG_05 \
"Error: reserving with a negative size didn't throw an exception\n"

#define EXCEPT_MSG_06 "Error: assign() should have thrown an exception\n"
#define EXCEPT_MSG_07 "Error: resize() should have thrown an exception\n"

typedef std::vector<int>::iterator                  stdIterator;
typedef ft::vector<int>::iterator                   ftIterator;
typedef std::vector<int>::const_iterator            stdConstIterator;
typedef ft::vector<int>::const_iterator             ftConstIterator;

typedef std::vector<int>::reverse_iterator          stdReverseIterator;
typedef ft::vector<int>::reverse_iterator           ftReverseIterator;
typedef std::vector<int>::const_reverse_iterator    stdConstReverseIterator;
typedef ft::vector<int>::const_reverse_iterator     ftConstReverseIterator;

#include "vector_tests.tpp"

#endif  // TESTS_VECTOR_VECTOR_TESTS_HPP_
