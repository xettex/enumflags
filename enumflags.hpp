// Enumflags
// Copyright (c) Xettex 2016
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#ifndef hpp_enumflags
#define hpp_enumflags

#include <limits>
#include <type_traits>

namespace enumflags {

template <typename T>
struct has_flags_attribute {
    static constexpr bool value{false};
};

template <typename T>
using is_enum_flags = std::integral_constant<
    bool,
    std::is_enum<T>::value || has_flags_attribute<T>::value>;

template <
    typename T,
    typename std::enable_if_t<is_enum_flags<T>::value>* = nullptr
>
struct flag_none {
    using value_type = T;
    static constexpr T value{};
};

template <
    typename T,
    typename std::enable_if_t<is_enum_flags<T>::value>* = nullptr
>
struct flag_all {
    using value_type = T;
    using underlying_type = std::underlying_type_t<T>;
    static constexpr T value{
        static_cast<T>(std::numeric_limits<underlying_type>::max())};
};

template <typename T>
constexpr std::enable_if_t<is_enum_flags<T>::value, T>
operator~(T rhs)
{
    using U = std::underlying_type_t<T>;
    return static_cast<T>(~static_cast<U>(rhs));
}

template <typename T>
constexpr std::enable_if_t<is_enum_flags<T>::value, T>
operator&(T lhs, T rhs)
{
    using U = std::underlying_type_t<T>;
    return static_cast<T>(static_cast<U>(lhs) & static_cast<U>(rhs));
}

template <typename T>
constexpr std::enable_if_t<is_enum_flags<T>::value, T>
operator|(T lhs, T rhs)
{
    using U = std::underlying_type_t<T>;
    return static_cast<T>(static_cast<U>(lhs) | static_cast<U>(rhs));
}

template <typename T>
constexpr std::enable_if_t<is_enum_flags<T>::value, T>
operator^(T lhs, T rhs)
{
    using U = std::underlying_type_t<T>;
    return static_cast<T>(static_cast<U>(lhs) ^ static_cast<U>(rhs));
}

template <typename T>
constexpr std::enable_if_t<is_enum_flags<T>::value, T&>
operator&=(T& lhs, T rhs)
{
    return lhs = lhs & rhs;
}

template <typename T>
constexpr std::enable_if_t<is_enum_flags<T>::value, T&>
operator|=(T& lhs, T rhs)
{
    return lhs = lhs | rhs;
}

template <typename T>
constexpr std::enable_if_t<is_enum_flags<T>::value, T&>
operator^=(T& lhs, T rhs)
{
    return lhs = lhs ^ rhs;
}

template <typename T>
constexpr std::enable_if_t<is_enum_flags<T>::value, bool>
has_exact_flags(T set, T subset)
{
    return (set & subset) == subset;
}

template <typename T>
constexpr std::enable_if_t<is_enum_flags<T>::value, bool>
has_any_flags(T set, T subset)
{
    return (set & subset) != flag_none<T>::value;
}

template <typename T>
constexpr std::enable_if_t<is_enum_flags<T>::value, T>
set_flags(T set, T subset)
{
    return set | subset;
}

template <typename T>
constexpr std::enable_if_t<is_enum_flags<T>::value, T>
unset_flags(T set, T subset)
{
    return set & ~subset;
}

template <typename T>
constexpr std::enable_if_t<is_enum_flags<T>::value, T>
toggle_flags(T set, T subset)
{
    return set ^ subset;
}

}

#endif // hpp_enumflags
