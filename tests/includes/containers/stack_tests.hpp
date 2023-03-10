/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TESTS_INCLUDES_VECTOR_TESTS_HPP_
#define TESTS_INCLUDES_VECTOR_TESTS_HPP_

#include <stack>
#include <deque>
#include <list>

#include "./utils.hpp"

#if STD == 1
    namespace ft = std;
#else
    #include "../../containers/stack.hpp"
#endif

template <typename T>
bool compare(T x, T y) {
    return x == y;
}

template <typename T>
void print(T x) {
    std::cout << x << ' ';
}

#endif  /* TESTS_INCLUDES_VECTOR_TESTS_HPP_ */
