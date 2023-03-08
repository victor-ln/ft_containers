
#include "./utils.hpp"

template <typename Container, typename T>
void printContainer(Container& container, void (*print)(T)) {
    typename Container::const_iterator it     = container.begin();
    typename Container::const_iterator ite    = container.end();

    while (it != ite) {
        print(*it);
        ++it;
    }
    std::cout << "\n";
    std::cout << "size: " << container.size() << "\n";
}

template <typename Container1, typename Container2, typename Compare>
bool compare_containers(const Container1& c1, const Container2& c2, Compare comp) {
    if (c1.size() != c2.size()) {
        return false;
    }
    typename Container1::const_iterator it1     = c1.begin();
    typename Container2::const_iterator it2     = c2.begin();
    typename Container1::const_iterator ite1    = c1.end();
    while (it1 != ite1) {
        if (!comp(*it1, *it2)) {
            return false;
        }
        ++it1, ++it2;
    }
    return true;
}
