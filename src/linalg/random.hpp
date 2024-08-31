#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

namespace rng
{

struct device
{
    inline static std::random_device handle;
};

template <typename T>
struct random
{
    T generate()
    {
        static std::uniform_int_distribution<T> dist;
        return dist(device::handle);
    }

    T generate(T start, T end)
    {
        static std::uniform_int_distribution<T> dist(start, end);
        return dist(device::handle);
    }
};

template <>
struct random<double>
{
    double generate()
    {
        static std::uniform_real_distribution<double> dist;
        return dist(device::handle);
    }

    double generate(double start, double end)
    {
        static std::uniform_real_distribution<double> dist(start, end);
        return dist(device::handle);
    }
};

template <>
struct random<float>
{
    float generate()
    {
        static std::uniform_real_distribution<float> dist;
        return dist(device::handle);
    }

    float generate(float start, float end)
    {
        static std::uniform_real_distribution<float> dist(start, end);
        return dist(device::handle);
    }
};

}; // namespace rng
#endif /* RANDOM_HPP */
