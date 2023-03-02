/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TESTS_SET_SET_TESTS_HPP_
#define TESTS_SET_SET_TESTS_HPP_

#include <set>

#include "../utils/utils.hpp"

#if STD == 1
    namespace ft = std;
#else
    #include "../../set/set.hpp"
    #include "../../algorithm/equal.hpp"
    #include "../../algorithm/lexicographical_compare.hpp"
#endif

#define EXCEPT_MSG_01 \
"Error: accessing out of range element didn't throw an exception\n"

#define EXCEPT_MSG_02 \
"resizing to a size greater than the maximum size didn't throw an exception\n"

#define EXCEPT_MSG_03 \
"Error: pushing back to a full set didn't throw an exception\n"

#define EXCEPT_MSG_04 \
"Error: resizing to a negative size didn't throw an exception\n"

#define EXCEPT_MSG_05 \
"Error: reserving with a negative size didn't throw an exception\n"

#define EXCEPT_MSG_06 "Error: assign() should have thrown an exception\n"
#define EXCEPT_MSG_07 "Error: resize() should have thrown an exception\n"

typedef std::set<int>::iterator                  stdIterator;
typedef ft::set<int>::iterator                   ftIterator;
typedef std::set<int>::const_iterator            stdConstIterator;
typedef ft::set<int>::const_iterator             ftConstIterator;

typedef std::set<int>::reverse_iterator          stdReverseIterator;
typedef ft::set<int>::reverse_iterator           ftReverseIterator;
typedef std::set<int>::const_reverse_iterator    stdConstReverseIterator;
typedef ft::set<int>::const_reverse_iterator     ftConstReverseIterator;

#include "set_tests.tpp"

#endif  // TESTS_SET_SET_TESTS_HPP_
