#pragma once

#include <string>
#include <sstream>

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
    is_iterable< std::remove_const_t< std::remove_reference_t<T> > >::value,
    std::string
> print(T&& container)
{
    if constexpr (std::is_constructible_v<std::string, T>)
    {
        return container;
    }
    else
    {
        auto&& begin_it = container.begin();
        auto&& end_it = container.end();

        if(begin_it == end_it)
            return "";

        std::stringstream ss;
        ss << *begin_it;
        for(auto&& it = ++begin_it; it != end_it; ++it)
        {
            ss << "." << *it;
        }

        return ss.str();
    }
}

template<typename T>
std::enable_if_t<
    std::is_arithmetic_v< std::remove_reference_t< std::remove_const_t<T> > >,
    std::string
> print(T&& val)
{
    std::array<T, sizeof(val)> tmp;
    constexpr std::remove_reference_t<T> mask = ~0;
    for(std::size_t sz = sizeof(val); sz > 0; --sz)
    {
        tmp[sz]((val >> ((sz - 1) * 8)) & mask);
    }
    return print(tmp);
}

template<typename T>
std::enable_if_t<
    std::is_pointer_v< std::remove_reference_t<T> >,
    std::string
> print(T&& val)
{
    // std::cout << __PRETTY_FUNCTION__ << std::endl;
    return print(*val);
}