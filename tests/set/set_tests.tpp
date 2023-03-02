/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "set_tests.hpp"

template <typename Container1, typename Container2>
bool compare_begin_and_end(const Container1& c1, const Container2& c2) {
    return (*c1.begin() == *c2.begin() && *(--c1.end()) == *(--c2.end()));
}

template <typename Container1, typename Container2>
bool compare_containers(const Container1& c1, const Container2& c2) {
    if (c1.size() != c2.size()) {
        return false;
    }
    typename Container1::const_iterator it1     = c1.begin();
    typename Container2::const_iterator it2     = c2.begin();
    typename Container1::const_iterator ite1    = c1.end();
    while (it1 != ite1) {
        if (*it1 != *it2) {
            return false;
        }
        ++it1, ++it2;
    }
    return true;
}

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

template <typename Container>
void printset(Container& set) {
  for (size_t i = 0; i < set.size(); i++) {
    std::cout << set[i] << " ";
  }
  std::cout << "\n";
  std::cout << "size: " << set.size() << "\n";
  std::cout << "capacity: " << set.capacity() << "\n";
}
