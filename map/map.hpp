/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef MAP_MAP_HPP_
#define MAP_MAP_HPP_

#include <functional>

#include "../utility/pair.hpp"
#include "../rb_tree/rb_tree.hpp"

#define MAP_TEMPLATE typename Key, \
   typename T, \
   typename Compare, \
   typename Allocator \

#define MAP_CLASS ft::map<Key, T, Compare, Allocator>

namespace ft {

template <
   typename Key,
   typename T,
   typename Compare = std::less<Key>,
   typename Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
    typedef Key                                     key_type;
    typedef	T                                       mapped_type;
    typedef ft::pair<const Key, T>                  value_type;
    typedef std::size_t                             size_type;
    typedef std::ptrdiff_t                          difference_type;
    typedef Compare                                 key_compare;
    typedef Allocator                               allocator_type;
    typedef value_type&                             reference;
    typedef const value_type&                       const_reference;
    typedef Allocator::pointer                      pointer;
    typedef Allocator::const_pointer                const_pointer;
    typedef ft::map_iterator<value_type>            iterator;
    typedef ft::map_iterator<value_type>            const_iterator;
    typedef ft::reverse_iterator<iterator>          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    map(Allocator alloc = Allocator());
    ~map(void);

    class value_compare : std::binary_function<value_type, value_type, bool> {
     protected:
        Compare comp;

        value_compare(Compare c) : comp(c) {}

     public:
        bool operator()(const value_type& lhs, const value_type& rhs) const {
            return comp(lhs, rhs);
        }
    };

 private:
    typedef rbTree<value_type, Allocator>* rbTreePtr;

    size_type        _size;
    allocator_type   _allocator;
    rbTreePtr        _rbTree;
};

}   // namespace ft

#endif  // MAP_MAP_HPP_
