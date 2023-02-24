/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef VECTOR_VECTOR_HPP_
#define VECTOR_VECTOR_HPP_

#include <stdexcept>
#include <memory>
#include <algorithm>
#include "../iterators/random_access_iter.hpp"
#include "../iterators/reverse_iter.hpp"
#include "../type_traits/type_traits.hpp"
#include "../algorithm/equal.hpp"
#include "../algorithm/lexicographical_compare.hpp"

namespace ft {

template <class T, class AllocTp = std::allocator<T> >
class vector {
 public:
    typedef T                                            value_type;
    typedef AllocTp                                      allocator_type;
    typedef std::size_t                                  size_type;
    typedef std::ptrdiff_t                               difference_type;
    typedef T&                                           reference;
    typedef const T&                                     const_reference;
    typedef T*                                           pointer;
    typedef const T*                                     const_pointer;

    typedef random_access_iter<pointer>                  iterator;
    typedef random_access_iter<const_pointer>            const_iterator;
    typedef reverse_iter<pointer>                        reverse_iterator;
    typedef reverse_iter<const_pointer>                  const_reverse_iterator;

    explicit vector(const allocator_type& alloc = allocator_type());

    explicit vector(size_type, const value_type& val = value_type(),
                      const allocator_type& alloc = allocator_type());

    vector(const vector&);

    template <class InputIterator>
    vector(InputIterator, InputIterator,
            const allocator_type& alloc = allocator_type());

    ~vector(void);

    vector&                operator=(const vector&);

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

    size_type           size(void) const;
    size_type           max_size(void) const;
    void                resize(size_type, value_type val = value_type());
    size_type           capacity(void) const;
    bool                empty(void) const;
    void                reserve(size_type);

    /*                          Element access:                           */
    reference           operator[](size_type);
    const_reference     operator[](size_type) const;
    reference           at(size_type);
    const_reference     at(size_type) const;
    reference           front(void);
    const_reference     front(void) const;
    reference           back(void);
    const_reference     back(void) const;
    value_type*         data(void);
    const value_type*   data(void) const;

    /*                              Modifiers:                            */
    template <class InputIterator>
    void                assign(InputIterator, InputIterator);
    void                assign(size_type, const value_type&);
    void                push_back(const value_type&);
    void                pop_back(void);
    iterator            insert(iterator, const value_type&);
    void                insert(iterator, size_type, const value_type&);
    template <class InputIterator>
    void                insert(iterator, InputIterator, InputIterator);
    iterator            erase(iterator);
    iterator            erase(iterator, iterator);
    void                swap(vector&);
    void                clear(void);

    /*                              Allocator:                            */
    allocator_type      get_allocator(void) const;

 private:
    pointer             _first;
    pointer             _last;
    pointer             _end_of_storage;
    allocator_type      _allocator;
    is_integral<T>      _is_integral;

    pointer             _allocate(size_type);

    void                _fill(pointer, const_reference, size_type);

    void                _destroy(pointer, pointer);

    void                _full_destroy_and_deallocate(void);

    void                _fill_initialiaze(size_type, const_reference);

    void                _init_dispatch(size_type, const_reference, true_type);

    template <class InputIter>
    void                _init_dispatch(InputIter, InputIter, false_type);

    void                _assign_dispatch(size_type, const_reference, true_type);

    template <class InputIter>
    void                _assign_dispatch(InputIter, InputIter, false_type);

    template <class Integer>
    void                _insert_dispatch(iterator, size_type, const Integer&,
                                         true_type);

    template <class InputIter>
    void                _insert_dispatch(iterator, InputIter, InputIter, false_type);

    void                _insert_dispatch(pointer, pointer, pointer);
}; /* class vector */

/*                          Relational Operators                      */
template <class T, class Alloc>
bool operator==(const vector<T, Alloc>&, const vector<T, Alloc>&);
template <class T, class Alloc>
bool operator!=(const vector<T, Alloc>&, const vector<T, Alloc>&);
template <class T, class Alloc>
bool operator< (const vector<T, Alloc>&, const vector<T, Alloc>&);
template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>&, const vector<T, Alloc>&);
template <class T, class Alloc>
bool operator> (const vector<T, Alloc>&, const vector<T, Alloc>&);
template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>&, const vector<T, Alloc>&);
template< class T, class Alloc >
void swap(vector<T, Alloc>&, vector<T, Alloc>&);
}  /* namespace ft */

#include "./vector.tpp"

#endif /* VECTOR_VECTOR_HPP_ */
