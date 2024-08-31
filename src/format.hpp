#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <format>
#include <string>

namespace str
{

template <typename T>
struct type_format
{
    static constexpr const char *value = "{}";
};

template <>
struct type_format<float>
{
    static constexpr const char *value = "{:.4f}";
};

template <>
struct type_format<double>
{
    static constexpr const char *value = "{:.4f}";
};

template <typename... Args>
constexpr std::string format(const std::string_view str_fmt, Args &&...args)
{
    return std::vformat(str_fmt, std::make_format_args(args...));
}

}; // namespace str

#endif /* FORMAT_HPP */
