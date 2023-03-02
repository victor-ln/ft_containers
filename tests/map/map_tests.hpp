/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TESTS_MAP_MAP_TESTS_HPP_
#define TESTS_MAP_MAP_TESTS_HPP_

#include <map>

#include "../utils/utils.hpp"

#if STD == 1
    namespace ft = std;
#else
    #include "../../map/map.hpp"
    #include "../../algorithm/equal.hpp"
    #include "../../algorithm/lexicographical_compare.hpp"
#endif

#define OK      "├── \x1b[32mOK\x1b[0m\n"
#define KO      "├── \x1b[31mKO\x1b[0m\n"
#define CYAN    "\033[1;36m"
#define BGWHITE "\033[1;37m"
#define RESET   "\033[0m"
#define RESULT  2

#define EXCEPT_MSG_01 \
"Error: accessing out of range element didn't throw an exception\n"

#define EXCEPT_MSG_02 \
"resizing to a size greater than the maximum size didn't throw an exception\n"

#define EXCEPT_MSG_03 \
"Error: pushing back to a full map didn't throw an exception\n"

#define EXCEPT_MSG_04 \
"Error: resizing to a negative size didn't throw an exception\n"

#define EXCEPT_MSG_05 \
"Error: reserving with a negative size didn't throw an exception\n"

#define EXCEPT_MSG_06 "Error: assign() should have thrown an exception\n"
#define EXCEPT_MSG_07 "Error: resize() should have thrown an exception\n"

typedef std::map<int>::iterator                  stdIterator;
typedef ft::map<int>::iterator                   ftIterator;
typedef std::map<int>::const_iterator            stdConstIterator;
typedef ft::map<int>::const_iterator             ftConstIterator;

typedef std::map<int>::reverse_iterator          stdReverseIterator;
typedef ft::map<int>::reverse_iterator           ftReverseIterator;
typedef std::map<int>::const_reverse_iterator    stdConstReverseIterator;
typedef ft::map<int>::const_reverse_iterator     ftConstReverseIterator;

int     comp(const int, const int);
void    printStatus(int);
void    printColor(const char* code, const char* message);

#include "map_tests.tpp"

#endif  // TESTS_MAP_MAP_TESTS_HPP_
