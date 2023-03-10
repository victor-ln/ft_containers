/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TESTS_INCLUDES_MAP_TESTS_HPP_
#define TESTS_INCLUDES_MAP_TESTS_HPP_

#include <map>

#include "../utils.hpp"

#if STD == 1
    namespace ft = std;
#else
    #include "../../../containers/map.hpp"
    #include "../../../utility/pair.hpp"
#endif

typedef std::map<std::string, int>              t_stdStrIntMap;
typedef t_stdStrIntMap::iterator                t_stdIterator;
typedef t_stdStrIntMap::const_iterator          t_stdConstIterator;
typedef t_stdStrIntMap::reverse_iterator        t_stdReverseIterator;
typedef t_stdStrIntMap::const_reverse_iterator  t_stdConstReverseIterator;

typedef ft::map<std::string, int>               t_ftStrIntMap;
typedef t_ftStrIntMap::iterator                 t_ftIterator;
typedef t_ftStrIntMap::const_iterator           t_ftConstIterator;
typedef t_ftStrIntMap::reverse_iterator         t_ftReverseIterator;
typedef t_ftStrIntMap::const_reverse_iterator   t_ftConstReverseIterator;

typedef ft::pair<std::string, int>              t_ftStrIntPair;
typedef std::pair<std::string, int>             t_stdStrIntPair;

typedef ft::pair<t_ftIterator, bool>            t_ftPairReturn;

bool operator==(const t_ftStrIntPair& x, const t_stdStrIntPair& y) {
    return x.first == y.first;
}

bool operator!=(const t_ftStrIntPair& x, const t_stdStrIntPair& y) {
    return x.first == y.first;
}

#if STD != 1

    bool operator==(const t_stdStrIntPair& x, const t_ftStrIntPair& y) {
        return x.first == y.first;
    }

    bool operator!=(const t_stdStrIntPair& x, const t_ftStrIntPair& y) {
        return x.first == y.first;
    }

    struct compare {
        bool operator()(const t_ftStrIntPair& x,
                        const t_stdStrIntPair& y) const {
            return x.first < y.first;
        }
        bool operator()(const t_stdStrIntPair& x,
                        const t_ftStrIntPair& y) const {
            return x.first < y.first;
        }
    };

    struct equal {
        bool operator()(const t_ftStrIntPair& x,
                        const t_stdStrIntPair& y) const {
            return x.first == y.first && x.second == y.second;
        }
    };

#endif

void print(const t_ftStrIntPair& x) {
    std::cout << "[" << x.first << ", " << x.second << "]";
}

struct s_pairs {
    t_ftStrIntPair        *ft;
    t_stdStrIntPair       *std;

    s_pairs() : ft(0), std(0) {}

    s_pairs(const s_pairs& src, std::size_t offset)
        :   ft(src.ft + offset),
            std(src.std + offset) {}
};


struct s_create_pairs {
    std::size_t         size;
    s_pairs             pairs;

    s_create_pairs() : size(0), pairs() {}

    explicit s_create_pairs(std::size_t _size) : size(_size), pairs() {
        if (size) {
            std::stringstream   ss;
            std::string         key;
            int                 value;

            pairs.ft = new t_ftStrIntPair[_size];
            pairs.std = new t_stdStrIntPair[_size];

            srand(_size);
            for (std::size_t i = 0; i < _size; ++i) {
                ss << i << " ", ss >> key;
                value = rand() % _size;
                pairs.ft[i] = t_ftStrIntPair(key, value);
                pairs.std[i] = t_stdStrIntPair(key, value);
            }
        }
    }
    ~s_create_pairs() {
        if (size) {
            delete[] pairs.ft;
            delete[] pairs.std;
        }
    }

    s_pairs    begin(void) const {
        return pairs;
    }

    s_pairs    end(void) const {
        return s_pairs(pairs, size);
    }
};

#endif  /* TESTS_INCLUDES_MAP_TESTS_HPP_ */
