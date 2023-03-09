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

    bool operator==(ft::pair<std::string, int>& x, std::pair<std::string, int>& y) {
        return x.first == y.first;
    }

    bool operator!=(ft::pair<std::string, int>& x, std::pair<std::string, int>& y) {
        return x.first == y.first;
    }

    bool operator==(std::pair<std::string, int>& x, ft::pair<std::string, int>& y) {
        return x.first == y.first;
    }

    bool operator!=(std::pair<std::string, int>& x, ft::pair<std::string, int>& y) {
        return x.first == y.first;
    }

    struct compare {
        bool operator()(const ft::pair<std::string, int>& x, const std::pair<std::string, int>& y) const {
            return x.first < y.first;
        }
        bool operator()(const std::pair<std::string, int>& x, const ft::pair<std::string, int>& y) const {
            return x.first < y.first;
        }
    };

    struct equal {
        bool operator()(const ft::pair<std::string, int>& x, const std::pair<std::string, int>& y) const {
            return x.first == y.first && x.second == y.second;
        }
    };

#endif

typedef ft::map<std::string, int>                           ftStrIntMap;
typedef ft::pair<std::string, int>                          ftStrIntPair;

typedef ft::map<std::string, int>::iterator                 ftIterator;
typedef ft::map<std::string, int>::const_iterator           ftConstIterator;
typedef ft::map<std::string, int>::reverse_iterator         ftReverseIterator;
typedef ft::map<std::string, int>::const_reverse_iterator   ftConstReverseIterator;

typedef std::map<std::string, int>                          stdStrIntMap;
typedef std::pair<std::string, int>                         stdStrIntPair;

typedef std::map<std::string, int>::iterator                stdIterator;
typedef std::map<std::string, int>::const_iterator          stdConstIterator;
typedef std::map<std::string, int>::reverse_iterator        stdReverseIterator;
typedef std::map<std::string, int>::const_reverse_iterator  stdConstReverseIterator;

void print(const ftStrIntPair& x) {
    std::cout << "[" << x.first << ", " << x.second << "]";
}

struct s_pairs {
    ftStrIntPair        *ft;
    stdStrIntPair       *std;

    s_pairs() : ft(0), std(0) {}

    s_pairs(s_pairs& src, std::size_t offset)
        :   ft(src.ft + offset),
            std(src.std + offset) {}
};


struct s_create_pairs {
    std::size_t         size;
    s_pairs             pairs;

    s_create_pairs() : size(0), pairs() {}

    s_create_pairs(std::size_t _size) : size(_size), pairs() {
        std::stringstream   ss;
        std::string         key;
        int                 value;

        pairs.ft = new ftStrIntPair[_size];
        pairs.std = new stdStrIntPair[_size];

        srand(_size);
        for (std::size_t i = 0; i < _size; ++i) {
            ss << i << " ", ss >> key;
            value = rand() % _size;
            pairs.ft[i] = ftStrIntPair(key, value);
            pairs.std[i] = stdStrIntPair(key, value);
        }
    }
    ~s_create_pairs() {
        delete[] pairs.ft;
        delete[] pairs.std;
    }

    s_pairs    begin(void) {
        return pairs;
    }

    s_pairs    end(void) {
        return s_pairs(pairs, size);
    }
};

#endif  /* TESTS_INCLUDES_MAP_TESTS_HPP_ */
