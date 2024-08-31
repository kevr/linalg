#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <functional>

template <typename T>
struct unary_op_base
{
    std::function<T(const T &)> func;

    unary_op_base(std::function<T(const T &)> func)
        : func(func)
    {
    }

    T operator()(const T &value) const
    {
        return func(value);
    }
};

template <typename T>
struct unary_op : public unary_op_base<T>
{
    template <typename Functor>
    unary_op(const T &lhs, Functor func)
        : unary_op_base<T>([lhs, func](const T &rhs) {
            return func(lhs, rhs);
        })
    {
    }

    template <typename Functor>
    unary_op(Functor func, const T &rhs)
        : unary_op_base<T>([rhs, func](const T &lhs) {
            return func(lhs, rhs);
        })
    {
    }
};

#endif /* ALGORITHM_HPP */
