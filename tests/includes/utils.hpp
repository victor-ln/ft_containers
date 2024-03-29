/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TESTS_INCLUDES_UTILS_HPP_
#define TESTS_INCLUDES_UTILS_HPP_

#include <limits>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <unistd.h>

#if STD != 1
    #define STD 0
#endif

#if TIME_TEST != 1
    #define TIME_TEST 0
    #define AMOUNT 10
#else
    #define AMOUNT 10000
#endif

#define OK      "├── \x1b[32mOK\x1b[0m\n"
#define KO      "├── \x1b[31mKO\x1b[0m\n"
#define CYAN    "\033[1;36m"
#define BGWHITE "\033[1;37m"
#define RESET   "\033[0m"
#define RESULT  2
#define DELAY   100

int     comp(const int, const int);
void    printStatus(int);
void    printColor(const char* code, const char* message);
void    printTime(int);
int*    createArray(size_t);

#include "./utils.tpp"

#endif	/* TESTS_INCLUDES_UTILS_HPP_ */
