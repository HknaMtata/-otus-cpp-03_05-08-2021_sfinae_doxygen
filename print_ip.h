#pragma once

#include <array>
#include <string>
#include <iostream>

/// Type trait. Check if type is iterable
template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T,
    std::void_t<
        decltype(std::declval<T>().begin()),
        decltype(std::declval<T>().end())
    >
> : std::true_type {};

/// Very important print function. Implementented with SFINAE idiom
template<typename T>
std::enable_if_t<
    is_iterable<
        std::conditional_t<
            std::is_constructible_v<std::string, T>, void, std::remove_const_t< std::remove_reference_t<T>>
        >
    >::value,
    void
> print(T&& container)
{
    auto&& begin_it = container.begin();
    auto&& end_it = container.end();
    if(begin_it != end_it)
    {
        std::cout << *begin_it;
        for(auto&& it = ++begin_it; it != end_it; ++it)
        {
            std::cout << "." << *it;
        }
    }
    std::cout << std::endl;
}

template<typename T>
std::enable_if_t<
    std::is_arithmetic_v< std::remove_reference_t< std::remove_const_t<T> > >,
    void
> print(T&& val)
{
    std::array< std::remove_const_t< std::remove_reference_t<T> >, sizeof(val)> tmp;
    for(std::size_t sz = 0; sz < sizeof(val); ++sz)
    {
        tmp[sz] = ((val >> ((sizeof(val) - (sz + 1)) * 8)) & ((1 << 8) - 1));
    }
    print(tmp);
}

template<typename T>
std::enable_if_t<
    std::is_constructible_v<std::string, T>,
    void
> print(T&& val)
{
    std::cout << val << std::endl;
}