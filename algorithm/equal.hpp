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

template <class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, 
                             InputIt2 last2) {
    while (first1 != last1) {
        if (first2 == last2 || *first2 < *first1) {
            return false;
        }
        if (*first1 < *first2) {
            return true;
        }
        ++first1; ++first2;
    }
    return (first2 != last2);
}

template <class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, 
                             InputIt2 last2, Compare comp) {
    while (first1 != last1) {
        if (first2 == last2 || comp(*first2, *first1)) {
            return false;
        }
        if (comp(*first1, *first2)) {
            return true;
        }
        ++first1; ++first2;
    }
    return (first2 != last2);    
}

}
