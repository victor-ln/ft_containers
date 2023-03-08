/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TESTS_INCLUDES_MAP_TESTS_HPP_
#define TESTS_INCLUDES_MAP_TESTS_HPP_

#include <map>

#include "./utils.hpp"

#if STD == 1
    namespace ft = std;
#else
    #include "../../containers/map.hpp"
    #include "../../utility/pair.hpp"

    typedef std::map<std::string, int>                          stdStrIntMap;
    typedef std::pair<std::string, int>                         stdStrIntPair;

    typedef std::map<std::string, int>::iterator                stdIterator;
    typedef std::map<std::string, int>::const_iterator          stdConstIterator;
    typedef std::map<std::string, int>::reverse_iterator        stdReverseIterator;
    typedef std::map<std::string, int>::const_reverse_iterator  stdConstReverseIterator;

#endif

typedef ft::map<std::string, int>                   ftStrIntMap;
typedef ft::pair<std::string, int>                  ftStrIntPair;

typedef ft::map<std::string, int>::iterator                 ftIterator;
typedef ft::map<std::string, int>::const_iterator           ftConstIterator;
typedef ft::map<std::string, int>::reverse_iterator         ftReverseIterator;
typedef ft::map<std::string, int>::const_reverse_iterator   ftConstReverseIterator;

bool compare(ftStrIntPair x, stdStrIntPair y) {
    return x.first == y.first && x.second == y.second;
}

void print(ftStrIntPair x) {
    std::cout << "[" << x.first << ", " << x.second << "]";
}

#endif  /* TESTS_INCLUDES_MAP_TESTS_HPP_ */
