#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "algorithm.hpp"
#include "defaults.hpp"
#include "format.hpp"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

namespace linalg
{

template <typename T, std::size_t Rows, std::size_t Columns>
class matrix
{
  private:
    T data[Rows][Columns] = {0};

  public:
    matrix() = default;

    matrix(const matrix &o)
    {
        operator=(o);
    }

    matrix &operator=(const matrix &o)
    {
        std::memcpy(&data[0][0], &o.data[0][0],
                    o.rows() * o.columns() * sizeof(T));
        return *this;
    }

    template <template <typename> typename Generator>
    matrix(Generator<T> gen)
    {
        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Columns; ++j) {
                data[i][j] = gen.generate();
            }
        }
    }

    T &operator[](std::size_t i, std::size_t j)
    {
        return data[i][j];
    }

    const T &operator()(std::size_t i, std::size_t j) const
    {
        return data[i][j];
    }

    matrix &operator-=(const matrix &o);

    const T &at(std::size_t i, std::size_t j) const
    {
        return data[i][j];
    }

    constexpr std::size_t rows() const
    {
        return Rows;
    }

    constexpr std::size_t columns() const
    {
        return Columns;
    }
};

template <typename T, std::size_t LR, std::size_t LC, std::size_t RR,
          std::size_t RC>
matrix<T, LR, RC> dot(const matrix<T, LR, LC> &lhs,
                      const matrix<T, RR, RC> &rhs)
{
    matrix<T, LR, RC> m; // lhs.rows() x rhs.columns()
    for (std::size_t i = 0; i < lhs.rows(); ++i) {
        for (std::size_t j = 0; j < rhs.columns(); ++j) {
            // sum(x1y1 + x2y2 + ... + xnyn)
            T sum{type_default<T>::value};
            for (std::size_t k = 0; k < rhs.rows(); ++k) {
                sum += lhs(i, k) * rhs(k, j);
            }
            m[i, j] = sum;
        }
    }
    return m;
}

template <typename T, std::size_t R, std::size_t C>
std::vector<T> dot(const std::vector<T> &vector, const matrix<T, R, C> &matrix)
{
    std::vector<T> results;
    for (std::size_t j = 0; j < matrix.columns(); ++j) {
        T sum{type_default<T>::value};
        for (std::size_t i = 0; i < matrix.rows(); ++i) {
            sum += vector[i] * matrix(i, j);
        }
        results.emplace_back(sum);
    }
    return results;
}

template <typename T, std::size_t R, std::size_t C, typename Functor>
matrix<T, R, C> transform(const matrix<T, R, C> &orig, Functor f)
{
    matrix<T, R, C> m;
    for (std::size_t i = 0; i < orig.rows(); ++i) {
        for (std::size_t j = 0; j < orig.columns(); ++j) {
            m[i, j] = f(orig(i, j));
        }
    }
    return m;
}

template <typename T, std::size_t R, std::size_t C, typename Functor>
matrix<T, R, C> transform(const linalg::matrix<T, R, C> &lhs,
                          const linalg::matrix<T, R, C> &rhs, Functor f)
{
    matrix<T, R, C> m;
    for (std::size_t i = 0; i < lhs.rows(); ++i) {
        for (std::size_t j = 0; j < lhs.columns(); ++j) {
            m[i, j] = f(lhs(i, j), rhs(i, j));
        }
    }
    return m;
}

template <typename T, std::size_t R, std::size_t C, typename Functor>
matrix<T, R, C> &transform_inplace(matrix<T, R, C> &m, const matrix<T, R, C> &o,
                                   Functor f)
{
    for (std::size_t i = 0; i < m.rows(); ++i) {
        for (std::size_t j = 0; j < m.columns(); ++j) {
            m[i, j] = f(m(i, j), o(i, j));
        }
    }
    return m;
}

}; // namespace linalg

// matrix + matrix
template <typename T, std::size_t R, std::size_t C>
linalg::matrix<T, R, C> operator+(const linalg::matrix<T, R, C> &lhs,
                                  const linalg::matrix<T, R, C> &rhs)
{
    return linalg::transform(lhs, rhs, std::plus<T>{});
}

// matrix - matrix
template <typename T, std::size_t R, std::size_t C>
linalg::matrix<T, R, C> operator-(const linalg::matrix<T, R, C> &lhs,
                                  const linalg::matrix<T, R, C> &rhs)
{
    return linalg::transform(lhs, rhs, std::minus<T>{});
}

// vector * matrix == dot(vector, matrix)
template <typename T, std::size_t R, std::size_t C>
std::vector<T> operator*(const std::vector<T> &v,
                         const linalg::matrix<T, R, C> &m)
{
    return linalg::dot(v, m);
}

// scalar + matrix
template <typename T, std::size_t R, std::size_t C>
linalg::matrix<T, R, C> operator+(const T &scalar,
                                  const linalg::matrix<T, R, C> &m)
{
    return linalg::transform(m, unary_op<T>(scalar, std::plus{}));
}

// matrix + scalar
template <typename T, std::size_t R, std::size_t C>
linalg::matrix<T, R, C> operator+(const linalg::matrix<T, R, C> &m,
                                  const T &scalar)
{
    return scalar + m;
}

// scalar - matrix
template <typename T, std::size_t R, std::size_t C>
linalg::matrix<T, R, C> operator-(const T &scalar,
                                  const linalg::matrix<T, R, C> &m)
{
    return linalg::transform(m, unary_op<T>(scalar, std::minus<T>{}));
}

// matrix - scalar
template <typename T, std::size_t R, std::size_t C>
linalg::matrix<T, R, C> operator-(const linalg::matrix<T, R, C> &m,
                                  const T &scalar)
{
    return linalg::transform(m, unary_op<T>(std::minus<T>{}, scalar));
}

// scalar * matrix
template <typename T, std::size_t R, std::size_t C>
linalg::matrix<T, R, C> operator*(const T &scalar,
                                  const linalg::matrix<T, R, C> &m)
{
    return linalg::transform(m, unary_op<T>(scalar, std::multiplies<T>{}));
}

// matrix * scalar
template <typename T, std::size_t R, std::size_t C>
linalg::matrix<T, R, C> operator*(const linalg::matrix<T, R, C> &m,
                                  const T &scalar)
{
    return scalar * m;
}

// scalar / matrix
template <typename T, std::size_t R, std::size_t C>
linalg::matrix<T, R, C> operator/(const T &scalar,
                                  const linalg::matrix<T, R, C> &m)
{
    return linalg::transform(m, unary_op<T>(scalar, std::divides<T>{}));
}

// matrix / scalar
template <typename T, std::size_t R, std::size_t C>
linalg::matrix<T, R, C> operator/(const linalg::matrix<T, R, C> &m,
                                  const T &scalar)
{
    return linalg::transform(m, unary_op<T>(std::divides<T>{}, scalar));
}

template <typename T, std::size_t R, std::size_t C>
linalg::matrix<T, R, C> &
linalg::matrix<T, R, C>::operator-=(const linalg::matrix<T, R, C> &o)
{
    return linalg::transform_inplace(*this, o, [](const T &lhs, const T &rhs) {
        return lhs - rhs;
    });
}

template <typename T, std::size_t R, std::size_t C>
std::ostream &operator<<(std::ostream &os,
                         const linalg::matrix<T, R, C> &matrix)
{
    auto handle_row = [&](auto i) {
        os << "> [";
        for (std::size_t j = 0; j < matrix.columns() - 1; ++j) {
            os << str::format("{:.4f}, ", matrix(i, j));
        }
        os << str::format("{:.4f}]", matrix(i, matrix.columns() - 1));
    };

    for (std::size_t i = 0; i < matrix.rows() - 1; ++i) {
        handle_row(i);
        os << '\n';
    }
    handle_row(matrix.rows() - 1);

    return os;
}

template <typename T, std::size_t R, std::size_t C>
std::string display(const linalg::matrix<T, R, C> &matrix)
{
    std::ostringstream ss;
    ss << matrix;
    return ss.str();
}

#endif /* MATRIX_HPP */
