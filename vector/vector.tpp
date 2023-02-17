/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "vector/vector.hpp"

namespace ft {

    template <class T, class AllocTp>
    vector<T, AllocTp>::vector(const allocator_type& alloc) {
        _first = _last = _end_of_storage = 0;
        _allocator = alloc;
    }

    template <class T, class AllocTp>
    vector<T, AllocTp>::vector(size_type n,
                            const value_type& val = value_type(),
                            const allocator_type& alloc = allocator_type()) {
        _allocator = alloc;
        _first = _allocate(n);
        _last = _first;
        _end_of_storage = _first + n;
        while (_last != _end_of_storage) {
            _allocator.construct(_last, val);
            ++_last;
        }
    }

    template <class T, class AllocTp>
    template <class InputIterator>
    vector<T, AllocTp>::vector(InputIterator first, InputIterator last,
                            const allocator_type& alloc = allocator_type()) {
        _allocator = alloc;
        _first = _allocate(std::distance(first, last));
        if (_is_integral) {
            _last = std::copy(first, last, _first);
        } else {
            _last = _construct(first, last, _first);
        }
        _end_of_storage = _last;
    }

    template <class T, class AllocTp>
    vector<T, AllocTp>::vector(const vector& src) {
        _first = _allocate(src.size());
        if (_is_integral) {
            _last = std::copy(src.begin(), src.end(), _first);
        } else {
            _last = _construct(src.begin(), src.end(), _first);
        }
        _end_of_storage = _last;
    }

    template <class T, class AllocTp>
    vector<T, AllocTp>::~vector(void) {
        if (!_is_integral)
            _destroy(_first, _last);
        _allocator.deallocate(_first, capacity());
        _first = _last = _end_of_storage = 0;
    }

    template <class T, class AllocTp>
    vector<T, AllocTp>& vector<T, AllocTp>::operator=(const vector& src) {
        if (this != &rhs) {
            if (size() && !_is_integral)
                _destroy(_first, _last);
            if (capacity() < src.size()) {
                if (capacity())
                    _allocator.deallocate(_first, capacity());
                _first = _allocate(src.size());
            }
            _last = std::copy(src.begin(), src.end(), _first);
            _end_of_storage = _last;
        }
        return *this;
    }

    /*                              Iterators:                            */
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator   begin(void) {
        iterator(_first);
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator   end(void) {
        iterator(_last);
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_iterator  begin(void) {
        const_iterator(_first);
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_iterator  end(void) {
        const_iterator(_last);
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::reverse_iterator    rbegin(void) {
        reverse_iterator(_first);
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::reverse_iterator    rend(void) {
        reverse_iterator(_last);
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_reverse_iterator rbegin(void) {
        const_reverse_iterator(_first);
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_reverse_iterator rend(void) {
        const_reverse_iterator(_last);
    }

    /*                              Capacity:                             */

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::size_type
                vector<T, AllocTp>::size(void) const {
        return _last - _first;
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::size_type
                vector<T, AllocTp>::max_size(void) const {
        return _allocator.max_size();
    }

    template <class T, class AllocTp>
    void vector<T, AllocTp>::resize(size_type n, value_type val = value_type()) {
        if (size() == n) { return; }
        if (n < size()) {
            if (!_is_integral)
                _destroy(_first + n, _last);
            _last = _first + n;
        } else {
            if (n > capacity()) {
                reserve(std::max(n, size() << 1));
            }
            if (!_is_integral) {
                _last = _construct(_last, _last + n, val);
            } else {
                std::fill(_last, _last + n, val);
                _last += n;
            }
        }
    }

    template <class T, class AllocTp>
    void     vector<T, AllocTp>::reserve(size_type newCapacity) {
        if (newCapacity <= capacity()) { return; }
        if (newCapacity > max_size()) {
            _full_destroy_and_deallocate();
            throw std::length_error();
        }
        pointer newFirst = _allocate(newCapacity);
        pointer newLast = 0;
        if (size()) {
            newLast = std::copy(_first, _last, newFirst);
            _full_destroy_and_deallocate();
        } else { newLast = newFirst; }
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
        return *(_first + n);
    }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::const_reference
                vector<T, AllocTp>::operator[](size_type n) const {
        return *(_first + n);
    }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::reference
                vector<T, AllocTp>::at(size_type n) {
        return *(_first + n);
    }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::const_reference
                vector<T, AllocTp>::at(size_type n) const {
        return *(_first + n);
    }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::reference
                        vector<T, AllocTp>::front(void) {
        return *_first;
    }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::const_reference
                vector<T, AllocTp>::front(void) const {
        return *_first;
    }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::reference
                vector<T, AllocTp>::back(void) {
        return *(_last - 1);
    }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::const_reference
                vector<T, AllocTp>::back(void) const {
        return *(_last - 1);
    }

    template <class T, class AllocTp>
    inline typename vector<T, AllocTp>::value_type*
                vector<T, AllocTp>::data(void) {
        return _first;
    }

    template <class T, class AllocTp>
    inline const typename vector<T, AllocTp>::value_type*
                    vector<T, AllocTp>::data(void) const {
        return _first;
    }

    /*                              Modifiers:                            */

    template <class T, class AllocTp>
    void vector<T, AllocTp>::assign(size_type n, const value_type& val) {
        if (n > capacity()) {
            vector tmp(n, val, _allocator);
            tmp.swap(*this);
        } else if (n > size()) {
            if (_is_integral) {
                std::fill(begin(), begin() + n, val);
            } else {
                std::fill(begin(), end(), val);
                _construct(_last, _last + n - size(), val);
            }
            _last = _first + n;
        } else {
            erase(std::fill_n(begin(), n, val), end());
        }
    }

    template <class T, class AllocTp>
    template <class InputIterator>
    void vector<T, AllocTp>::assign(InputIterator first, InputIterator last) {
        if (ft::is_integral<InputIterator>) {
            assign(static_cast<size_type>(first), static_cast<value_type>(last));
        } else {
            size_type   n = std::distance(first, last);
            if (n > capacity()) {
                vector tmp(first, last);
                tmp.swap(*this);
            } else {
                std::copy(first, last, _first);
                _last = _first + n;
            }
        }
    }

    template <class T, class AllocTp>
    void vector<T, AllocTp>::push_back(const value_type& value) {
        if (_last == _end_of_storage) {
            reserve(size() << 1);
        }
        _allocator.construct(_last, value);
        ++_last;
    }

    template <class T, class AllocTp>
    inline void vector<T, AllocTp>::pop_back(void) {
        _allocator.destroy(--_last);
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator
                vector<T, AllocTp>::insert(iterator pos, const value_type& val) {
        if (_last == _end_of_storage) {
            size_type   dist = pos.base() - _first;
            reserve(size() << 1);
            pos = iterator(_first + dist);
        }
        pointer posPtr = pos.base();
        if (posPtr != _last) {
            std::copy_backward(posPtr, _last - 1, _last);
        }
        _allocator.construct(posPtr, val);
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
        pointer     posStart = pos.base();
        pointer     posEnd = posStart + n;
        if (posStart != _last) {
            std::copy_backward(posStart, _last - 1, _last + n);
        }
        if (!_is_integral) {
            _construct(posStart, posEnd, val);
        } else {
            std::fill(posStart, posEnd, val);
        }
        _last += n;
    }

    template <class T, class AllocTp>
    template <class InputIterator>
    void vector<T, AllocTp>::insert(iterator pos,
                                    InputIterator first, InputIterator last) {
        size_type n = std::distance(first, last);
        if (n > capacity() - size()) {
            size_type   dist = pos.base() - _first;
            reserve(size() + std::max(n, size()));
            pos = iterator(_first + dist);
        }
        if (pos.base() != _last) {
            std::copy_backward(pos.base(), _last - 1, _last + n);
        }
        std::copy(first, last, pos);
        _last += n;
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator vector<T, AllocTp>::erase(iterator pos) {
        if (pos != end()) {
            if (pos + 1 != end()) {
                std::copy(pos + 1, _last, pos);
            }
            _allocator.destroy(--_last);
        }
        return pos;
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator
                vector<T, AllocTp>::erase(iterator first, iterator last) {
        if (first == end()) {
            return first;
        }
        if (last == end()) {
            if (!_is_integral)
                _destroy(first.base(), _last);
            _last = first.base();
            return first;
        }
        pointer newLast = (std::copy(last, end(), first)).base();
        if (!_is_integral)
            _destroy(newLast, _last);
        _last -= last - first;
        return first;
    }

    template <class T, class AllocTp>
    void vector<T, AllocTp>::swap(vector& rhs) {
        std::swap(_first, rhs._first);
        std::swap(_last, rhs._last);
        std::swap(_end_of_storage, rhs._end_of_storage);
        std::swap(_allocator, rhs._allocator);
        std::swap(_is_integral, rhs._is_integral);
    }

    template <class T, class AllocTp>
    void vector<T, AllocTp>::clear(void) {
        if (!_is_integral)
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
    void vector<T, AllocTp>::_destroy(pointer first, pointer last) {
        while (first != last) {
            first->~T();
            ++first;
        }
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::pointer
            vector<T, AllocTp>::_construct(pointer first, pointer last,
                                                    const value_type& val) {
        while (first != last) {
            _allocator.construct(first, val);
            ++first;
        }
        return first;
    }

    template <class T, class AllocTp>
    template <class InputIter>
    typename vector<T, AllocTp>::pointer
            vector<T, AllocTp>::_construct(InputIter first, InputIter last,
                                                    pointer result) {
        while (first != last) {
            _allocator.construct(result, *first);
            ++first;
            ++result;
        }
        return result;
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::pointer
                vector<T, AllocTp>::_allocate(size_type n) {
        pointer newBlock;
        try {
            newBlock = _allocator.allocate(n);
        } catch (...) {
            _full_destroy_and_deallocate();
            throw std::bad_alloc();
        }
        return newBlock;
    }

    template <class T, class AllocTp>
    void vector<T, AllocTp>::_full_destroy_and_deallocate(void) {
        if (!_is_integral)
            _destroy(first, last);
        _allocator.deallocate(first, capacity());
    }
}   // namespace ft
