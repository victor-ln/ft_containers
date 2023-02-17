/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef ALGORITHM_EQUAL_HPP_
#define ALGORITHM_EQUAL_HPP_

namespace ft {

template<class InputIt1, class InputIt2>
inline bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
    while (first1 != last1) {
        if (*first1 != *first2) {
            return false;
        }
        ++first1; ++first2;
    }
    return true;
}

template<class InputIt1, class InputIt2, class BinaryPredicate>
inline bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2,
                  BinaryPredicate pred) {
    while (first1 != last1) {
        if (!pred(*first1, *first2)) {
            return false;
        }
        ++first1; ++first2;
    }
    return true;
}

}   // namespace ft

#endif  // ALGORITHM_EQUAL_HPP_
