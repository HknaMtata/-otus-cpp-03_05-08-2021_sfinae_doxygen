#pragma once

#include <array>
#include <string>
#include <iostream>

template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T,
    std::void_t<
        decltype(std::declval<T>().begin()),
        decltype(std::declval<T>().end())
    >
> : std::true_type {};

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
    auto get_byte = [&val](const std::size_t& byte) {
        return (val >> ((sizeof(val) - (byte + 1)) * 8)) & ((1 << 8) - 1);
    };

    std::size_t pos = 0;
    std::cout << get_byte(pos);

    ++pos;
    for(; pos < sizeof(val); ++pos)
    {
        std::cout << "." << get_byte(pos);
    }

    std::cout << std::endl;
}

template<typename T>
std::enable_if_t<
    std::is_constructible_v<std::string, T>,
    void
> print(T&& val)
{
    std::cout << val << std::endl;
}