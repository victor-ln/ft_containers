/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#include "./vector.hpp"

namespace ft {

    template <class T, class AllocTp>
    vector<T, AllocTp>::vector(void) {
        _first = _allocator.allocate(1);
        _last = _first;
        _end_of_storage = _first + 1;
    }

    template <class T, class AllocTp>
    vector<T, AllocTp>::vector(const vector& src) {
        if (_first)
            this->~vector();
        _first = _allocator.allocate(src.size());
        _last = std::uninitialized_copy(src.cbegin(), src.cend(), _first);
        _end_of_storage = src._end_of_storage;
    };

    template <class T, class AllocTp>
    vector<T, AllocTp>::~vector(void) {
        std::_Destroy(_first, _last);
        _allocator.deallocate(_first, this->capacity());
    }

    template <class T, class AllocTp>
    vector<T, AllocTp>& vector<T, AllocTp>::operator=(const vector&) {
        
    }

    /*                              Iterators:                            */
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator   begin(void) {
        return 
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator   end(void) {
        
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_iterator  begin(void) {
        
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_iterator  end(void) {
        
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::reverse_iterator    rbegin(void) {
        
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::reverse_iterator    rend(void) {
        
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_reverse_iterator rbegin(void) {
        
    }
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_reverse_iterator rend(void) {
        
    }

    /*                              Capacity:                             */

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::size_type   vector<T, AllocTp>::size(void) const {
        return _last - _first;
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::size_type   vector<T, AllocTp>::max_size(void) const {
        return _allocator.max_size();
    }

    /**
     * Resizes the container so that it contains n elements.
     * 
     * If n is smaller than the current container size, 
     * the content is reduced to its first n elements, 
     * removing those beyond (and destroying them).
     * 
     * If n is greater than the current container size, the content is 
     * expanded by inserting at the end as many elements as needed to reach 
     * a size of n. If val is specified, the new elements are initialized 
     * as copies of val, otherwise, they are value-initialized.
     * 
     * If n is also greater than the current container capacity, an
     * automatic reallocation of the allocated storage space takes place.
     * Notice that this function changes the actual content 
     * of the container by inserting or erasing elements from it.
     * 
     * @param n New container size, expressed in number of elements.
     * Member type size_type is an unsigned integral type.
     * @param val Object whose content is copied to the added elements 
     * in case that n is greater than the current container size.
     * If not specified, the default constructor is used instead.
     * Member type value_type is the type of the elements in the container,
     *  defined in vector as an alias of the first template parameter (T)
     */
    template <class T, class AllocTp>
    void        vector<T, AllocTp>::resize(size_type n, value_type val = value_type()) {

    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::size_type   vector<T, AllocTp>::capacity(void) const {
        return _end_of_storage - _first;
    }

    template <class T, class AllocTp>
    bool    vector<T, AllocTp>::empty(void) const {
        return this->_first == this->_last;
    }

    template <class T, class AllocTp>
    void        vector<T, AllocTp>::reserve(size_type) {

    }

    /*                          Element access:                           */

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::reference   vector<T, AllocTp>::operator[](size_type n) {
        return *(_first + n);
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_reference vector<T, AllocTp>::operator[](size_type n) const {
        return *(_first + n);
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::reference   vector<T, AllocTp>::at(size_type n) {
        return *(_first + n);
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_reference vector<T, AllocTp>::at(size_type n) const {
        return *(_first + n);
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::reference   vector<T, AllocTp>::front(void) {
        return *_first;
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_reference vector<T, AllocTp>::front(void) const {
        return *_first;
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::reference   vector<T, AllocTp>::back(void) {
        return *(_last - 1);
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const_reference vector<T, AllocTp>::back(void) const {
        return *(_last - 1);
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::value_type* vector<T, AllocTp>::data(void) noexcept {
        return _first;
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::const value_type*   vector<T, AllocTp>::data(void) const noexcept {
        return _first;
    }

    /*                              Modifiers:                            */
    template <class T, class AllocTp>
    template <class InputIterator>
    void                vector<T, AllocTp>::assign(InputIterator first, InputIterator last) {

    }
    template <class T, class AllocTp>
    void                vector<T, AllocTp>::assign(size_type, const value_type&) {

    }

    template <class T, class AllocTp>
    void    vector<T, AllocTp>::push_back(const value_type& value) {
        if (_last == _end_of_storage) {
            _realloc_data(this->size() << 1);
        }
        _allocator.construct(_last, value);
        ++_last;
    }

    template <class T, class AllocTp>
    void    vector<T, AllocTp>::pop_back(void) {
        _allocator.destroy(--_last);
    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator            vector<T, AllocTp>::insert(iterator, const value_type&) {

    }

    template <class T, class AllocTp>
    void                vector<T, AllocTp>::insert(iterator, size_type, const value_type&) {

    }

    template <class T, class AllocTp>
    template <class InputIterator>
    void    vector<T, AllocTp>::insert(iterator, InputIterator, InputIterator) {

    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator   vector<T, AllocTp>::erase(iterator) {

    }

    template <class T, class AllocTp>
    typename vector<T, AllocTp>::iterator   vector<T, AllocTp>::erase(iterator, iterator) {

    }

    template <class T, class AllocTp>
    void                vector<T, AllocTp>::swap(vector&) {

    }

    template <class T, class AllocTp>
    void    vector<T, AllocTp>::clear(void) {
        std::_Destroy(_first, _last);
        _last = _first;
    }

    /*                              Allocator:                            */
    template <class T, class AllocTp>
    typename vector<T, AllocTp>::allocator_type  vector<T, AllocTp>::get_allocator(void) const {
        return allocator_type(_allocator);
    }

    template <class T, class AllocTp>
    void    vector<T, AllocTp>::_realloc_data(size_type n) {
        pointer newBlock = _allocator.allocate(n);
        pointer newLast = std::uninitialized_copy(_first, _last, newBlock);
        _end_of_storage = newBlock + n;
        std::_Destroy(_first, _last);
        _allocator.deallocate(_first, size());
        _first = newBlock;
        _last = newLast;
    }
}
