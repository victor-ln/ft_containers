/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef MAP_MAP_HPP_
#define MAP_MAP_HPP_

#include <functional>

#include "../rb_tree/rb_tree.hpp"

#define MAP_TEMPLATE typename Key, typename T, typename Compare, typename AllocTp
#define MAP_CLASS ft::map<Key, T, Compare, AllocTp>

namespace ft {

template <typename Key, typename T, typename Compare = std::less<Key>,
   typename AllocTp = std::allocator<ft::pair<const Key, T> > >
class map {
 private:
    typedef rb_tree<Key, T, Compare, AllocTp>   _rbTreeBase;
    typedef _rbTreeBase*                        _rbTree;

    _rbTree    _rbTreeBase;
 public:
    using typename _rbTreeBase::key_type;
    using typename _rbTreeBase::mapped_type;
    using typename _rbTreeBase::value_type;
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
            return comp(lhs, rhs);
        }
    };

    map(AllocTp alloc = AllocTp());
    ~map(void);

    /*                              Iterators:                            */
    iterator               begin(void);
    iterator               end(void);
    const_iterator         begin(void) const;
    const_iterator         end(void) const;

    reverse_iterator       rbegin(void);
    reverse_iterator       rend(void);
    const_reverse_iterator rbegin(void) const;
    const_reverse_iterator rend(void) const;

    /*                              Capacity:                             */
    size_type              size(void) const;
    size_type              max_size(void) const;
    bool                   empty(void) const;

    /*                          Element access:                           */
    reference              operator[](size_type);
    const_reference        operator[](size_type) const;
    reference              at(size_type);
    const_reference        at(size_type) const;

    /*                              Modifiers:                            */
    pair<iterator, bool>   insert(const value_type&);
    iterator               insert(iterator, const value_type&);
    template <class InputIterator>
    void                   insert(InputIterator, InputIterator);
    void                   erase(iterator);
    size_type              erase(const key_type&);
    void                   erase(iterator, iterator);
    void                   swap(map& x);
    void                   clear(void);


    /*                              Observers:                            */
    key_compare            key_comp(void);
    value_compare          value_comp(void);

    /*                              Lookup:                               */
    iterator               find(const key_type&);
    const_iterator         find(const key_type&) const;
    size_type              count(const key_type&) const;
    iterator               lower_bound(const key_type&);
    const_iterator         lower_bound(const key_type&) const;
    iterator               upper_bound(const key_type&);
    const_iterator         upper_bound(const key_type&) const;
    ft::pair<iterator,iterator>              equal_range(const key_type&);
    ft::pair<const_iterator,const_iterator>  equal_range(const key_type&) const

    /*                              Allocator:                            */
    allocator_type      get_allocator(void) const;
};

}   // namespace ft

#endif  // MAP_MAP_HPP_
