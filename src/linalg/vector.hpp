#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "algorithm.hpp"
#include "format.hpp"
#include "random.hpp"
#include "string.hpp"
#include <functional>
#include <ostream>
#include <vector>

namespace vector
{

template <typename T>
std::vector<T> make_vector(std::size_t n, std::function<T(std::size_t)> f)
{
    std::vector<T> v{};
    for (std::size_t i = 0; i < n; ++i)
        v.emplace_back(f(i));
    return v;
}

template <typename T>
std::vector<T> random(std::size_t n)
{
    rng::random<T> r;
    return make_vector<T>(n, [&r](std::size_t) -> T {
        return r.generate();
    });
}

}; // namespace vector

namespace linalg
{

template <typename T, typename Functor>
std::vector<T> transform(const std::vector<T> &orig, Functor f)
{
    std::vector<T> v;
    for (std::size_t i = 0; i < orig.size(); ++i) {
        v.emplace_back(f(orig.at(i)));
    }
    return v;
}

template <typename T, typename Functor>
std::vector<T> transform(const std::vector<T> &lhs, const std::vector<T> &rhs,
                         Functor f)
{
    std::vector<T> v;
    for (std::size_t i = 0; i < lhs.size(); ++i) {
        v.emplace_back(f(lhs.at(i), rhs.at(i)));
    }
    return v;
}

template <typename T, typename Functor>
std::vector<T> &transform_inplace(std::vector<T> &v, const std::vector<T> &o,
                                  Functor f)
{
    for (std::size_t i = 0; i < v.size(); ++i) {
        v[i] = f(v.at(i), o.at(i));
    }
    return v;
}

}; // namespace linalg

// v1 + v2 == [v1[0] + v2[0], ..., vn[0] + vn[1]]
template <typename T>
std::vector<T> operator+(const std::vector<T> &lhs, const std::vector<T> &rhs)
{
    return linalg::transform(lhs, rhs, std::plus<T>{});
}

// v1 - v2 == [v1[0] - v2[0], ..., vn[0] - vn[1]]
template <typename T>
std::vector<T> operator-(const std::vector<T> &lhs, const std::vector<T> &rhs)
{
    return linalg::transform(lhs, rhs, std::minus<T>{});
}

// v1 * v2 == [v1[0] * v2[0], ..., vn[0] * vn[1]]
template <typename T>
std::vector<T> operator*(const std::vector<T> &lhs, const std::vector<T> &rhs)
{
    return linalg::transform(lhs, rhs, std::multiplies<T>{});
}

// v1 * v2 == [v1[0] * v2[0], ..., vn[0] * vn[1]]
template <typename T>
std::vector<T> operator/(const std::vector<T> &lhs, const std::vector<T> &rhs)
{
    return linalg::transform(lhs, rhs, std::divides<T>{});
}

// scalar + vector
template <typename T>
std::vector<T> operator+(const T &scalar, const std::vector<T> &orig)
{
    return linalg::transform(orig, unary_op<T>(scalar, std::plus<T>{}));
}

// vector + scalar
template <typename T>
std::vector<T> operator+(const std::vector<T> &orig, const T &scalar)
{
    return scalar + orig;
}

// scalar - vector
template <typename T>
std::vector<T> operator-(const T &scalar, const std::vector<T> &orig)
{
    return linalg::transform(orig, unary_op<T>(scalar, std::minus<T>{}));
}

// vector - scalar
template <typename T>
std::vector<T> operator-(const std::vector<T> &orig, const T &scalar)
{
    return linalg::transform(orig, unary_op<T>(std::minus<T>{}, scalar));
}

// scalar * vector
template <typename T>
std::vector<T> operator*(const T &scalar, const std::vector<T> &orig)
{
    return linalg::transform(orig, unary_op<T>(scalar, std::multiplies<T>{}));
}

// vector * scalar
template <typename T>
std::vector<T> operator*(const std::vector<T> &orig, const T &scalar)
{
    return scalar * orig;
}

// scalar * vector
template <typename T>
std::vector<T> operator/(const T &scalar, const std::vector<T> &orig)
{
    return linalg::transform(orig, unary_op<T>(scalar, std::divides<T>{}));
}

// vector * scalar
template <typename T>
std::vector<T> operator/(const std::vector<T> &orig, const T &scalar)
{
    return linalg::transform(orig, unary_op<T>(std::divides<T>{}, scalar));
}

// in-place subtraction
template <typename T>
std::vector<T> &operator-=(std::vector<T> &v, const std::vector<T> &o)
{
    return linalg::transform_inplace(v, o, std::minus<T>{});
}

template <typename T>
std::vector<T> operator-(const std::vector<T> &v)
{
    return linalg::transform(v, std::negate<T>{});
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vector)
{
    const std::size_t last = vector.size() - 1;
    os << '[';
    for (std::size_t i = 0; i < last; ++i) {
        os << str::format("{:.4f}, ", vector.at(i));
    }
    os << str::format("{:.4f}]", vector.at(last));
    return os;
}

template <typename T>
std::string display(const std::vector<T> &v)
{
    return str::format("[{}]", str::join(v));
}

#endif /* VECTOR_HPP */
