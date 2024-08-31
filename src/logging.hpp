#ifndef LOGGING_HPP
#define LOGGING_HPP

#include "format.hpp"
#include <iostream>
#include <sstream>
#include <string_view>

template <typename... Args>
int print_stream(std::ostream &os, int rc, const std::string_view &fmt,
                 Args &&...args)
{
    std::stringstream ss;
    ss << str::format(fmt, std::forward<Args>(args)...) << '\n';
    os << ss.str();
    return rc;
}

template <typename... Args>
int print(const std::string_view &fmt, Args &&...args)
{
    return print_stream(std::cout, 0, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
int eprint(const std::string_view &fmt, Args &&...args)
{
    return print_stream(std::cerr, 1, "error: {}",
                        str::format(fmt, std::forward<Args>(args)...));
}

#endif /* LOGGING_HPP */
