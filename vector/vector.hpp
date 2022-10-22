#pragma once
#ifndef FT_CONTAINERS_INCLUDES_FT_CONTAINERS_HPP_
#define FT_CONTAINERS_INCLUDES_FT_CONTAINERS_HPP_

#include <memory>

namespace ft {
    template <class Tp, class AllocTp = std::allocator<Tp> >
    class vector {
        typedef Tp                                          value_type;
        typedef allocator_type                              AllocTp;
        typedef std::size_t                                 size_type;
        typedef std::ptrdiff_t                              difference_type;
        typedef typename AllocTp::reference                 reference;
        typedef typename AllocTp::const_reference           const_reference;
        typedef typename AllocTp::pointer                   pointer;
        typedef typename AllocTp::const_pointer             const_pointer;

     public:
        vector(void) {}
        vector(const vector&);
        ~vector(void) {}

        vector& operator=(const vector&);

        /*                              Iterators:                            */
        begin(void);
        end(void);
        rbegin(void);
        rend(void);

        /*                              Capacity:                             */

        size_type   size(void) const;
        size_type   max_size(void) const;

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
        void        resize(size_type n, value_type val = value_type());
        size_type   capacity(void) const;
        bool        empty(void) const;
        void        reserve(size_type);

        /*                          Element access:                           */
        reference           operator[](size_type);
        const_reference     operator[](size_type) const;
        reference           at(size_type);
        const_reference     at(size_type) const;
        reference           front(void);
        const_reference     front(void) const;
        reference           back(void);
        const_reference     back(void) const;
        value_type*         data(void) noexcept;
        const value_type*   data(void) const noexcept;

        /*                              Modifiers:                            */
        template <class InputIterator>
        void                assign(InputIterator first, InputIterator last);
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
        
    };
    /*                          Relational Operators                      */
    template <class T, class Alloc>
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
    bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
    bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
    bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
    bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
    template <class T, class Alloc>
    bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
};


#endif /* FT_CONTAINERS_INCLUDES_FT_CONTAINERS_HPP_ */
