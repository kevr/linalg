#ifndef DEFAULTS_HPP
#define DEFAULTS_HPP

template <typename T>
struct type_default
{
    constexpr static T value = T{};
};

template <>
struct type_default<double>
{
    constexpr static double value = 0.0;
};

template <>
struct type_default<int>
{
    constexpr static double value = 0;
};

#endif /* DEFAULTS_HPP */
