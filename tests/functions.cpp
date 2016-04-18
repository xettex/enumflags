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

#include <enumflags.hpp>
#include <cassert>

using namespace enumflags;

enum class flag_type {
    none = 0,

    a = 1 << 0,
    b = 1 << 1,

    ab = a | b,
};

template <>
struct enumflags::has_flags_attribute<::flag_type> {
    static constexpr bool value{true};
};

int main()
{
    auto f = flag_type::none;

    f = set_flags(f, flag_type::a | flag_type::b);
    assert(f == flag_type::ab);

    f = unset_flags(f, flag_type::b);
    assert(f == flag_type::a);
    assert(has_any_flags(f, flag_type::ab));

    f = toggle_flags(f, flag_type::b);
    assert(f == flag_type::ab);
    assert(has_exact_flags(f, flag_type::ab));

    return 0;
}
