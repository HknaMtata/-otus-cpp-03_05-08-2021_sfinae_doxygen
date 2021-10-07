#pragma once

#include <array>
#include <string>
#include <iostream>
#include <list>
#include <vector>

namespace detail
{

template<typename T>
void print_stl_container(const T container)
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

}

template<typename T>
std::enable_if_t<
    std::is_same_v<
        std::vector<typename std::remove_const_t<std::remove_reference_t<T>>::value_type>,
        typename std::remove_const_t<std::remove_reference_t<T>>
    >
> print(const T container)
{
    if constexpr (std::is_reference_v<std::remove_const_t<T>>) {
        detail::print_stl_container(std::forward<T>(container));
    } else {
        detail::print_stl_container(container);
    }
}

template<typename T>
std::enable_if_t<
    std::is_same_v<
        std::list<typename std::remove_const_t<std::remove_reference_t<T>>::value_type>,
        typename std::remove_const_t<std::remove_reference_t<T>>
    >
> print(T container)
{
    if constexpr (std::is_reference_v<std::remove_const_t<T>>) {
        detail::print_stl_container(std::forward(container));
    } else {
        detail::print_stl_container(container);
    }
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