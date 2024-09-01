#ifndef STRING_HPP
#define STRING_HPP

#include "format.hpp"
#include "matrix.hpp"
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

template <typename T, std::size_t R, std::size_t C>
std::string join(const linalg::matrix<T, R, C> &m,
                 const std::string &delim = ", ")
{
    std::ostringstream ss;
    auto f = [&](std::size_t i) {
        std::vector<T> v;
        for (std::size_t j = 0; j < m.columns(); ++j) {
            v.emplace_back(m(i, j));
        }
        ss << '[' << join(v, delim) << ']';
    };

    ss << '[';
    auto last = m.rows() - 1;
    for (std::size_t i = 0; i < last; ++i) {
        f(i);
        ss << delim;
    }
    f(last);
    ss << ']';

    return ss.str();
}

}; // namespace str

#endif /* STRING_HPP */
