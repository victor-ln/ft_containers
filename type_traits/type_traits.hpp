/* Copyright © 2022 Victor Nunes, Licensed under the MIT License. */

#ifndef TYPE_TRAITS_TYPE_TRAITS_HPP_
#define TYPE_TRAITS_TYPE_TRAITS_HPP_

namespace ft {

template<typename T, T v>
struct integral_constant {
    static const T                      value = v;
    typedef T                           value_type;
    typedef integral_constant<T, v>     type;

    operator bool() const { return value; }
    value_type operator()() const { return value; }
};

typedef integral_constant<bool, true>     true_type;
typedef integral_constant<bool, false>    false_type;

template <typename T> struct is_integral : public false_type {};

template <> struct is_integral<bool> : public true_type {};
template <> struct is_integral<char> : public true_type {};
template <> struct is_integral<wchar_t> : public true_type {};
template <> struct is_integral<short> : public true_type {};
template <> struct is_integral<int> : public true_type {};
template <> struct is_integral<long> : public true_type {};
template <> struct is_integral<long long> : public true_type {};
template <> struct is_integral<unsigned char> : public true_type {};
template <> struct is_integral<unsigned short> : public true_type {};
template <> struct is_integral<unsigned int> : public true_type {};
template <> struct is_integral<unsigned long> : public true_type {};
template <> struct is_integral<unsigned long long> : public true_type {};

/** 
 * The type T is enabled as member type enable_if::type if Cond is true.
 * Otherwise, enable_if::type is not defined.
 */

template<bool Cond, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

}   // namespace ft

#endif  // TYPE_TRAITS_TYPE_TRAITS_HPP_
