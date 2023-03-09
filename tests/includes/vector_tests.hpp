/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TESTS_INCLUDES_VECTOR_TESTS_HPP_
#define TESTS_INCLUDES_VECTOR_TESTS_HPP_

#include <vector>

#include "./utils.hpp"

#if STD == 1
    namespace ft = std;
#else
    #include "../../containers/vector.hpp"

    typedef std::vector<int>::iterator                  stdIterator;
    typedef std::vector<int>::const_iterator            stdConstIterator;
    typedef std::vector<int>::reverse_iterator          stdReverseIterator;
    typedef std::vector<int>::const_reverse_iterator    stdConstReverseIterator;

#endif

typedef ft::vector<int>::iterator                   ftIterator;
typedef ft::vector<int>::const_iterator             ftConstIterator;
typedef ft::vector<int>::reverse_iterator           ftReverseIterator;
typedef ft::vector<int>::const_reverse_iterator     ftConstReverseIterator;

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

template <typename Container>
static void accessorTestAux1(Container& c, long n) {
    try {
        (void)c.at(n);
        std::cerr << EXCEPT_MSG_01;
        printStatus(false);
    } catch (const std::exception& e) {
        printStatus(true);
    }
}

template <typename Container>
static void accessorTestAux2(Container& c, long n) {
    try {
        (void)c[n];
        std::cerr << EXCEPT_MSG_01;
        printStatus(false);
    } catch (const std::exception& e) {
        printStatus(true);
    }
}

template <typename T>
bool compare(T x, T y) {
    return x == y;
}

template <typename T>
void print(T x) {
    std::cout << x << ' ';
}

#endif  /* TESTS_INCLUDES_VECTOR_TESTS_HPP_ */
