/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "vector.hpp"
#define LENGTH_ERR_MSG "cannot create std::vector larger than max_size()"

namespace ft {
    template <class T, class AllocTp>
    vector<T, AllocTp>::vector(const allocator_type& alloc) : _first(0),
                            _last(0), _end_of_storage(0), _allocator(alloc) {}

    template <class T, class AllocTp>
    vector<T, AllocTp>::vector(size_type n, const value_type& val,
                            const allocator_type& alloc) : _allocator(alloc) {

        _first = _allocate(n);
        _end_of_storage = _first + n;
        _last = _end_of_storage;
        std::uninitialized_fill_n(_first, n, val);
    }

    template <class T, class AllocTp>
    template <class InputIterator>
    vector<T, AllocTp>::vector(InputIterator first, InputIterator last,
                            const allocator_type& alloc) : _first(0),
                            _last(0), _end_of_storage(0), _allocator(alloc) {
        _init_dispatch(first, last, ft::is_integral<InputIterator>());
    }

    template <class T, class AllocTp>
    vector<T, AllocTp>::vector(const vector& src) {
        _first = _allocate(src.size());
        _last = std::uninitialized_copy(src._first, src._last, _first);
        _end_of_storage = _last;
    }

    template <class T, class AllocTp>
    vector<T, AllocTp>::~vector(void) {
        _destroy(_first, _last);
        _allocator.deallocate(_first, capacity());
        _first = _last = _end_of_storage = 0;
    }

    template <class T, class AllocTp>
    vector<T, AllocTp>& vector<T, AllocTp>::operator=(const vector& src) {
        if (this != &src) {
            size_type srcSize(src.size());
            if (srcSize > capacity()) {
                _full_destroy_and_deallocate();
                _first = _allocate(srcSize);
                _last = std::uninitialized_copy(src._first, src._last, _first);
                _end_of_storage = _first + srcSize;
            } else {
                size_type oldSize(size());
                if (oldSize >= srcSize) {
                    _destroy(std::copy(src._first, src._last, _first), _last);
                } else {
                    std::copy(src._first, src._first + oldSize, _first);
                    std::uninitialized_copy(src._first + oldSize, src._last, _last);
                }
            }
        }
        return *this;
    }

    /*                              Iterators:                            */
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator   vector<T, AllocTp>::begin(void) {
        return iterator(_first);
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator   vector<T, AllocTp>::end(void) {
        return iterator(_last);
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_iterator
                vector<T, AllocTp>::begin(void) const {
        return const_iterator(_first);
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_iterator
                vector<T, AllocTp>::end(void) const {
        return const_iterator(_last);
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::reverse_iterator
                vector<T, AllocTp>::rbegin(void) {
        return reverse_iterator(_last);
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::reverse_iterator
                vector<T, AllocTp>::rend(void) {
        return reverse_iterator(_first);
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_reverse_iterator
                vector<T, AllocTp>::rbegin(void) const {
        return const_reverse_iterator(_last);
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_reverse_iterator
                vector<T, AllocTp>::rend(void) const {
        return const_reverse_iterator(_first);
    }

    /*                              Capacity:                             */

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::size_type
                vector<T, AllocTp>::size(void) const { return _last - _first; }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::size_type
                vector<T, AllocTp>::max_size(void) const {
        return _allocator.max_size();
    }

    template <class T, class AllocTp>
    void vector<T, AllocTp>::resize(size_type n, value_type val) {
        if (size() == n) { return; }
        if (n < size()) {
            _destroy(_first + n, _last);
            _last = _first + n;
        } else {
            if (n > capacity()) {
                reserve(std::max(n, size() << 1));
            }
            pointer oldLast(_last);
            _last += n - size();
            std::uninitialized_fill(oldLast, _last, val);
        }
    }

    template <class T, class AllocTp>
    void     vector<T, AllocTp>::reserve(size_type newCapacity) {
        if (newCapacity <= capacity()) { return; }
        pointer newFirst = _allocate(newCapacity);
        pointer newLast = newFirst;
        if (size()) {
            newLast = std::uninitialized_copy(_first, _last, newFirst);
            _full_destroy_and_deallocate();
        }
        _first = newFirst;
        _last = newLast;
        _end_of_storage = newFirst + newCapacity;
    }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::size_type
                        vector<T, AllocTp>::capacity(void) const {
        return _end_of_storage - _first;
    }

    template <class T, class AllocTp>
    inline bool    vector<T, AllocTp>::empty(void) const {
        return _first == _last;
    }

    /*                          Element access:                           */

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::reference
                vector<T, AllocTp>::operator[](size_type n) {
        if (n >= capacity()) {
            throw std::out_of_range("out_of_range");
        }
        return *(_first + n);
    }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::const_reference
                vector<T, AllocTp>::operator[](size_type n) const {
        if (n >= capacity()) {
            throw std::out_of_range("out_of_range");
        }
        return *(_first + n);
    }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::reference
                vector<T, AllocTp>::at(size_type n) {
        if (n >= capacity()) {
            throw std::out_of_range("out_of_range");
        }
        return *(_first + n);
    }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::const_reference
                vector<T, AllocTp>::at(size_type n) const {
        if (n >= capacity()) {
            throw std::out_of_range("out_of_range");
        }
        return *(_first + n);
    }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::reference
                        vector<T, AllocTp>::front(void) { return *_first; }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::const_reference
                vector<T, AllocTp>::front(void) const { return *_first; }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::reference
                vector<T, AllocTp>::back(void) { return *(_last - 1); }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::const_reference
                vector<T, AllocTp>::back(void) const { return *(_last - 1); }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::value_type*
                vector<T, AllocTp>::data(void) { return _first; }

    template <class T, class AllocTp>
    inline const typename vector<T, AllocTp>::value_type*
                    vector<T, AllocTp>::data(void) const { return _first; }

    /*                              Modifiers:                            */

    template <class T, class AllocTp>
    void vector<T, AllocTp>::assign(size_type n, const value_type& val) {
        if (n > capacity()) {
            vector tmp(n, val, _allocator);
            tmp.swap(*this);
        } else if (n > size()) {
            std::fill(_first, _last, val);
            std::uninitialized_fill(_last, _first + n, val);
            _last = _first + n;
        } else {
            std::fill(_first, _first + n, val);
            erase(iterator(_first + n), end());
        }
    }

    template <class T, class AllocTp>
    template <class InputIterator>
    void vector<T, AllocTp>::assign(InputIterator first, InputIterator last) {
        _assign_dispatch(first, last, is_integral<InputIterator>());
    }

    template <class T, class AllocTp>
    void vector<T, AllocTp>::push_back(const value_type& value) {
        if (_last == _end_of_storage) {
            reserve(std::max(size() << 1, static_cast<size_type>(1)));
        }
        _allocator.construct(_last, value);
        ++_last;
    }

    template <class T, class AllocTp>
    inline void vector<T, AllocTp>::pop_back(void) {
        if (!empty()) {
            _allocator.destroy(--_last);
        }
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator
            vector<T, AllocTp>::insert(iterator pos, const value_type& val) {
        if (_last == _end_of_storage) {
            size_type   dist = pos.base() - _first;
            reserve(std::max(size() << 1, static_cast<size_type>(1)));
            pos = iterator(_first + dist);
        }
        pointer posPtr = pos.base();
        if (posPtr != _last) {
            _allocator.construct(_last, *(_last - 1));
            std::copy_backward(posPtr, _last - 1, _last);
            *posPtr = val;
        } else {
            _allocator.construct(posPtr, val);
        }
        ++_last;
        return pos;
    }

    template <class T, class AllocTp>
    void vector<T, AllocTp>::insert(iterator pos, size_type n,
                                    const value_type& val) {
        if (n > capacity() - size()) {
            size_type   dist = pos.base() - _first;
            reserve(size() + std::max(n, size()));
            pos = iterator(_first + dist);
        }
        pointer     posPtr = pos.base();
        pointer     oldLast(_last);
        size_type   posN(_last - posPtr);

        if (posN > n) {
            std::uninitialized_copy(_last - n, _last, _last);
            _last += n;
            std::copy_backward(posPtr, oldLast - n, oldLast);
            std::fill_n(posPtr, n, val);
        } else {
            std::uninitialized_fill_n(_last, n - posN, val);
            _last += n - posN;
            std::uninitialized_copy(posPtr, oldLast, _last);
            _last += posN;
            std::fill(posPtr, oldLast, val);
        }
    }

    template <class T, class AllocTp>
    template <class InputIterator>
    void vector<T, AllocTp>::insert(iterator pos,
                                    InputIterator first, InputIterator last) {
        _insert_dispatch(pos, first, last, ft::is_integral<InputIterator>());
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator
                vector<T, AllocTp>::erase(iterator pos) {
        if (pos + 1 != end()) {
            std::copy(pos.base() + 1, _last, pos.base());
        }
        _allocator.destroy(--_last);
        return pos;
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator
                vector<T, AllocTp>::erase(iterator first, iterator last) {
        if (first == end()) { return first; }
        if (last == end()) {
            _destroy(first.base(), _last);
            _last = first.base();
            return first;
        }
        pointer newLast = std::copy(last.base(), _last, first.base());
        _destroy(newLast, _last);
        _last -= last - first;
        return first;
    }

    template <class T, class AllocTp>
    void vector<T, AllocTp>::swap(vector& rhs) {
        pointer tmp_first = rhs._first;
        pointer tmp_last = rhs._last;
        pointer tmp_end_of_storage = rhs._end_of_storage;

        rhs._first = _first;
        rhs._end_of_storage = _end_of_storage;
        rhs._last = _last;

        _first = tmp_first;
        _end_of_storage = tmp_end_of_storage;
        _last = tmp_last;
    }

    template <class T, class AllocTp>
    void vector<T, AllocTp>::clear(void) {
        _destroy(_first, _last);
        _last = _first;
    }

    /*                              Allocator:                            */
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::allocator_type
                vector<T, AllocTp>::get_allocator(void) const {
        return allocator_type(_allocator);
    }

/*                          Private member functions                          */

    template <class T, class AllocTp>
    void vector<T, AllocTp>::_init_dispatch(size_type n,
                                            const value_type& val, true_type) {
        _first = _allocate(n);
        _end_of_storage = _first + n;
        _last = _end_of_storage;
        std::uninitialized_fill_n(_first, n, val);
    }

    template <class T, class AllocTp>
    template <class InputIterator>
    void vector<T, AllocTp>::_init_dispatch(InputIterator first,
                                              InputIterator last, false_type) {
        _first = _allocate(std::distance(first, last));
        _last = std::uninitialized_copy(first, last, _first);
        _end_of_storage = _last;
    }

    template <class T, class AllocTp>
    template <class Integer>
    void vector<T, AllocTp>::_insert_dispatch(iterator pos, size_type n,
                                              const Integer& val, true_type) {
        insert(pos, n, val);
    }

    template <class T, class AllocTp>
    template <class InputIter>
    void vector<T, AllocTp>::_insert_dispatch(iterator pos, InputIter first,
                                              InputIter last, false_type) {
        size_type   n = last - first;
        pointer     firstPtr(&*first), lastPtr(&*last), posPtr(pos.base());

        if (n > static_cast<size_type>(_end_of_storage - _last)) {
            size_type len(size() + std::max(n, size()));
            pointer newFirst(_allocate(len));
            pointer newLast(newFirst);

            try {
                newLast = std::uninitialized_copy(_first, posPtr, newFirst);
                newLast = std::uninitialized_copy(firstPtr, lastPtr, newLast);
                newLast = std::uninitialized_copy(posPtr, _last, newLast);
            } catch (...) {
                _destroy(newFirst, newLast);
                _allocator.deallocate(newFirst, n);
                throw;
            }
            _full_destroy_and_deallocate();
            _first = newFirst;
            _last = newLast;
            _end_of_storage = _first + len;
        } else {
            pointer     oldLast(_last);
            size_type   posN(_last - posPtr);

            if (posN > n) {
                std::uninitialized_copy(_last - n, _last, _last);
                _last += n;
                std::copy_backward(posPtr, oldLast - n, oldLast);
                std::copy(firstPtr, lastPtr, posPtr);
            } else {
                pointer mid(firstPtr + posN);
                std::uninitialized_copy(mid, lastPtr, _last);
                _last += n - posN;
                std::uninitialized_copy(posPtr, oldLast, _last);
                _last += posN;
                std::copy(firstPtr, mid, posPtr);
            }
        }
    }

    template <class T, class AllocTp>
    void vector<T, AllocTp>::_assign_dispatch(size_type first,
        const value_type& last, true_type) {
        assign(first, last);
    }

    template <class T, class AllocTp>
    template <class InputIter>
    void vector<T, AllocTp>::_assign_dispatch(InputIter first, InputIter last,
                                                false_type) {
        if (static_cast<size_type>(last - first) > capacity()) {
            vector tmp(first, last);
            tmp.swap(*this);
        } else {
            _last = std::uninitialized_copy(first, last, _first);
        }
    }

    template <class T, class AllocTp>
    void vector<T, AllocTp>::_destroy(pointer first, pointer last) {
        if (_is_integral) { return; }
        while (first != last) {
            first->~T();
            ++first;
        }
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::pointer
                vector<T, AllocTp>::_allocate(size_type n) {
        if (n > max_size()) {
            throw std::length_error(LENGTH_ERR_MSG);
        }
        return _allocator.allocate(n);
    }

    template <class T, class AllocTp>
    void vector<T, AllocTp>::_full_destroy_and_deallocate(void) {
        _destroy(_first, _last);
        _allocator.deallocate(_first, capacity());
    }

/*                          Non-member functions                              */
    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return lhs.size() == rhs.size() && \
                ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator< (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(),
                                            rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator> (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
        return !(lhs < rhs);
    }
}   // namespace ft
