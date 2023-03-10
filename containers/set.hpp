/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef CONTAINERS_SET_HPP_
#define CONTAINERS_SET_HPP_

#include <functional>
#include <memory>

#include "../algorithm/equal.hpp"
#include "../algorithm/lexicographical_compare.hpp"
#include "../utility/pair.hpp"
#include "../rb_tree/rb_tree.hpp"

namespace ft {

template <typename Key, typename Compare = std::less<Key>,
        typename AllocTp = std::allocator<Key> >
class set {
 public:
    typedef Key                                     key_type;
    typedef Key                                     value_type;
    typedef std::size_t                             size_type;
    typedef std::ptrdiff_t                          difference_type;
    typedef Compare                                 key_compare;
    typedef Compare                                 value_compare;
    typedef AllocTp                                 allocator_type;
    typedef value_type&                             reference;
    typedef const value_type&                       const_reference;
    typedef value_type*                             pointer;
    typedef const value_type*                       const_pointer;

    typedef ft::rb_tree_iter<pointer>               iterator;
    typedef ft::rb_tree_iter<const_pointer>         const_iterator;
    typedef ft::reverse_iter<iterator>              reverse_iterator;
    typedef ft::reverse_iter<const_iterator>        const_reverse_iterator;

    set() : _key_comp(key_compare()),
            _rb_tree(key_compare(), AllocTp()) {}

    explicit set(const Compare& comp, const AllocTp& alloc = AllocTp())
        :   _key_comp(comp),
            _rb_tree(comp, alloc) {}

    template<class InputIt>
    set(InputIt first, InputIt last,
        const Compare& comp = Compare(),
        const AllocTp& alloc = AllocTp())
        :   _key_comp(comp),
            _rb_tree(comp, alloc) { insert(first, last); }

    set(const set& src)
        :   _key_comp(key_compare()),
            _rb_tree(value_compare(key_compare()), AllocTp()) { *this = src; }

    ~set() {}

    set&    operator=(const set& src) {
        if (&src != this) {
            _rb_tree.clear();
            insert(src.begin(), src.end());
        }
        return *this;
    }

    /*                              Allocator:                            */

    AllocTp                get_allocator(void) const { return AllocTp(); }

    /*                              Iterators:                            */

    iterator               begin(void) { return _rb_tree.begin(); }
    iterator               end(void) { return _rb_tree.end(); }
    const_iterator         begin(void) const { return _rb_tree.begin(); }
    const_iterator         end(void) const { return _rb_tree.end(); }

    reverse_iterator       rbegin(void) { return reverse_iterator(end()); }
    reverse_iterator       rend(void) { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin(void) const {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator rend(void) const {
        return const_reverse_iterator(begin());
    }

    /*                              Capacity:                             */

    size_type              size(void) const { return _rb_tree.size(); }
    size_type              max_size(void) const { return _rb_tree.max_size(); }
    bool                   empty(void) const { return !_rb_tree.size(); }

    /*                              Observers:                            */

    key_compare            key_comp(void) const { return Compare(); }
    value_compare          value_comp(void) const { return Compare(); }


    /*                              Modifiers:                            */

    ft::pair<iterator, bool>   insert(const value_type& data) {
        node_pointer    node = _rb_tree.search(data);
        if (node) {
            return ft::make_pair(iterator(node), false);
        }
        return ft::make_pair(_rb_tree.insert(data), true);
    }

    iterator   insert(iterator pos, const value_type& data) {
        if (_rb_tree.upper_bound(data) != pos.base()) {
            return _rb_tree.insert(data);
        } else {
            return _rb_tree.insert(data, pos.base());
        }
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        while (first != last) {
            _rb_tree.insert(*first);
            ++first;
        }
    }

    void erase(iterator pos) {
        _rb_tree.remove(*pos);
    }

    size_type  erase(const key_type& key) {
        return _rb_tree.remove(key);
    }

    void erase(iterator first, iterator last) {
        iterator it;
        while (first != last) {
            it = first++;
            _rb_tree.remove(*it);
        }
    }

    void swap(set& x) { _rb_tree.swap(x._rb_tree); }
    void clear(void) { _rb_tree.clear(); }

    /*                              Lookup:                               */

    iterator               find(const key_type& key) {
        node_pointer node = _rb_tree.search(key);
        if (!node)
            return _rb_tree.end();
        return iterator(node);
    }
    const_iterator         find(const key_type& key) const {
        const_node_pointer node = _rb_tree.search(key);
        if (!node)
            return _rb_tree.end();
        return const_iterator(node);
    }

    size_type              count(const key_type& key) const {
        return _rb_tree.search(key) != 0;
    }

    iterator               lower_bound(const key_type& key) {
        return iterator(
            _rb_tree.lower_bound(key));
    }

    const_iterator         lower_bound(const key_type& key) const {
        return const_iterator(
            _rb_tree.lower_bound(key));
    }

    iterator               upper_bound(const key_type& key) {
        return iterator(
            _rb_tree.upper_bound(key));
    }

    const_iterator         upper_bound(const key_type& key) const {
        return const_iterator(
            _rb_tree.upper_bound(key));
    }

    ft::pair<iterator, iterator>    equal_range(const key_type& key) {
        return ft::make_pair(
            lower_bound(key),
            upper_bound(key));
    }

    ft::pair<const_iterator, const_iterator>
                equal_range(const key_type& key) const {
        return ft::make_pair(
            lower_bound(key),
            upper_bound(key));
    }

 private:
    typedef rb_tree<value_type, value_compare, AllocTp>     rbTreeBase;
    typedef node<value_type>*                               node_pointer;
    typedef const node<value_type>*                         const_node_pointer;

    key_compare _key_comp;
    rbTreeBase  _rb_tree;
}; /* class set */

/*                          Relational Operators                      */

template <typename Key, typename Compare, typename AllocTp>
bool  operator==(const set<Key, Compare, AllocTp>& x,
                 const set<Key, Compare, AllocTp>& y) {
    return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template <typename Key, typename Compare, typename AllocTp>
bool  operator!=(const set<Key, Compare, AllocTp>& x,
                 const set<Key, Compare, AllocTp>& y) {
    return !(x == y);
}

template <typename Key, typename Compare, typename AllocTp>
bool  operator<(const set<Key, Compare, AllocTp>& x,
                 const set<Key, Compare, AllocTp>& y) {
    return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <typename Key, typename Compare, typename AllocTp>
bool  operator<=(const set<Key, Compare, AllocTp>& x,
                 const set<Key, Compare, AllocTp>& y) {
    return !(y < x);
}

template <typename Key, typename Compare, typename AllocTp>
bool  operator>(const set<Key, Compare, AllocTp>& x,
                 const set<Key, Compare, AllocTp>& y) {
    return y < x;
}

template <typename Key, typename Compare, typename AllocTp>
bool  operator>=(const set<Key, Compare, AllocTp>& x,
                 const set<Key, Compare, AllocTp>& y) {
    return !(x < y);
}

/*                          Non member functions                      */

template <typename Key, typename Compare, typename AllocTp>
void  swap(set<Key, Compare, AllocTp>& x, set<Key, Compare, AllocTp>& y) {
    x.swap(y);
}

}   /* namespace ft */

#endif  /* CONTAINERS_SET_HPP_ */
