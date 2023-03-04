/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef CONTAINERS_MAP_HPP_
#define CONTAINERS_MAP_HPP_

#include <functional>

#include "../rb_tree/rb_tree.hpp"

namespace ft {

template <typename Key, typename T, typename Compare = std::less<Key>,
   typename AllocTp = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
    typedef Key                                       key_type;
    typedef	T                                         mapped_type;
    typedef ft::pair<const Key, T>                    value_type;

 private:
    typedef rb_tree<value_type, Compare, AllocTp>     _rbTreeBase;

    _rbTreeBase   _rbTree;
 public:
    using typename _rbTreeBase::size_type;
    using typename _rbTreeBase::difference_type;
    using typename _rbTreeBase::key_compare;
    using typename _rbTreeBase::allocator_type;
    using typename _rbTreeBase::reference;
    using typename _rbTreeBase::const_reference;
    using typename _rbTreeBase::pointer;
    using typename _rbTreeBase::const_pointer;
    using typename _rbTreeBase::iterator;
    using typename _rbTreeBase::const_iterator;
    using typename _rbTreeBase::reverse_iterator;
    using typename _rbTreeBase::const_reverse_iterator;

    class value_compare : std::binary_function<value_type, value_type, bool> {
     protected:
        Compare comp;

        value_compare(Compare c) : comp(c) {}

     public:
        bool operator()(const value_type& lhs, const value_type& rhs) const {
            return comp(lhs.first, rhs.first);
        }
    };

    map() {}

    map(const Compare&, AllocTp alloc = AllocTp()) {}

    template<class InputIt>
    map(InputIt first, InputIt last, const Compare& comp = Compare(),
                   const AllocTp& alloc = AllocTp()) {
         insert(first, last);
    }
    map(const map& src) {}

    ~map() {}

    map&                   operator=(const map& src) {
        _rbTree = src._rbTree;
    }

    /*                              Iterators:                            */

    iterator               begin(void) { return _rbTree.begin(); }
    iterator               end(void) { return _rbTree.end(); }
    const_iterator         begin(void) const { return _rbTree.begin(); }
    const_iterator         end(void) const { return _rbTree.end(); }

    reverse_iterator       rbegin(void) { return reverse_iterator(end()); }
    reverse_iterator       rend(void) { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin(void) const {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator rend(void) const {
        return const_reverse_iterator(begin());
    }

    /*                              Capacity:                             */

    size_type              size(void) const { _rbTree.size() }
    size_type              max_size(void) const { _rbTree.max_size() }
    bool                   empty(void) const { !_rbTree.size() }

    /*                          Element access:                           */

    mapped_type&           operator[](const key_type& k) {}
    const mapped_type&     operator[](const key_type& k) const {}
    mapped_type&           at(const key_type& k) {}
    const mapped_type&     at(const key_type& k) const {}

    /*                              Modifiers:                            */

    pair<iterator, bool>   insert(const value_type& pair) {
        iterator it = find(pair.first);
        if (it != end()) {
            return make_pair(it, false);
        }
        _rbTree.insert(pair);
        it = find(pair.first);
        return make_pair(it, true);
    }

    iterator               insert(iterator pos, const value_type& pair) {
        
    }

    template <class InputIterator>
    void                   insert(InputIterator first, InputIterator last) {
        while (first != last) {
            insert(first);
            ++first;
        }
    }
    iterator               erase(iterator) {}
    iterator               erase(iterator, iterator) {}
    size_type              erase(const key_type&) {}
    void                   swap(map& x) {}
    void                   clear(void) {}


    /*                              Observers:                            */

    key_compare            key_comp(void) const {}
    value_compare          value_comp(void) const {}

    /*                              Lookup:                               */

    iterator               find(const key_type&) {}
    const_iterator         find(const key_type&) const {}
    size_type              count(const key_type&) const {}
    iterator               lower_bound(const key_type&) {}
    const_iterator         lower_bound(const key_type&) const {}
    iterator               upper_bound(const key_type&) {}
    const_iterator         upper_bound(const key_type&) const {}
    ft::pair<iterator, iterator>              equal_range(const key_type&) {}
    ft::pair<const_iterator, const_iterator>  equal_range(const key_type&) const {}

    /*                              Allocator:                            */
    AllocTp                get_allocator(void) const { return AllocTp(); }
};

}  /* namespace ft */

#endif   /* CONTAINERS_MAP_HPP_ */
