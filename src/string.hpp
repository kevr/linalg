#ifndef STRING_HPP
#define STRING_HPP

#include "format.hpp"
#include <sstream>
#include <string>
#include <vector>

namespace str
{

template <typename T>
std::string join(const std::vector<T> &v, const std::string &delim = ", ")
{
    constexpr auto fmt = type_format<T>::value;

    std::ostringstream ss;
    std::size_t last = v.size() - 1;
    for (std::size_t i = 0; i < last; ++i) {
        ss << str::format(fmt, v.at(i)) << delim;
    }
    ss << str::format(fmt, v.at(last));

    return ss.str();
}

}; // namespace str

#endif /* STRING_HPP */
