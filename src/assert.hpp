#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <stdexcept>
#include <string>

struct assertion_error : public std::logic_error
{
    using std::logic_error::logic_error;
};

template <typename T>
void assert_condition(T condition, const std::string &message)
{
    if (!condition) {
        throw assertion_error(message);
    }
}

#endif /* ASSERT_HPP */
