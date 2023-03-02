/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TESTS_UTILS_UTILS_HPP_
#define TESTS_UTILS_UTILS_HPP_

#define OK      "├── \x1b[32mOK\x1b[0m\n"
#define KO      "├── \x1b[31mKO\x1b[0m\n"
#define CYAN    "\033[1;36m"
#define BGWHITE "\033[1;37m"
#define RESET   "\033[0m"
#define RESULT  2

#include <limits>
#include <cstdlib>
#include <iostream>

int     comp(const int, const int);
void    printStatus(int);
void    printColor(const char* code, const char* message);

#endif	// TESTS_UTILS_UTILS_HPP_
