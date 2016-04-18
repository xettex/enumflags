Introduction
============

Enumflags is a minimalistic, header-only library for utilizing enum
types as flag types in C++14.  It provides bitwise operators suitable
for use with flags, helpers for obtaining empty and full values for flag
types, and functions for performing common flag operations, such as
setting, unsetting, and toggling flags and determining the state of
flags.  This functionality is applicable to enum-class types and is
enabled through the presence of a simple type-specialization for each
intended flag type.

Requirements
============

The Enumflags implementation makes heavy use of C++14 features.  A
sufficiently compliant compiler is necessary in order to compile code
written using Enumflags.  The only library used in Enumflags is the STL,
which must also have adequate support for C++14.

Installation
============

Enumflags is a header-only library, contained within a single header.
To install, simply copy `enumflags.hpp` to an appropriate include
directory.  This may be done system-wide or locally per-project.  The
library is licensed under the highly-permissive ISC license and is legal
to include in any codebase.

Use
===

To use Enumflags, include `enumflags.hpp` and use the `enumflags`
namespace.  After defining your enum type `T`, inform the Enumflags
library that the type is intended for use as a flags type by
specializing the `enumflags::has_flags_attribute` structure:

```cpp
template <>
struct enumflags::has_flags_attribute<T> {
    static constexpr bool value{true};
};
```

This enables the following features:

- Traits
  - `bool enumflags::is_enum_flags<T>::value`
  - `T enumflags::flag_none<T>::value`
  - `T enumflags::flag_all<T>::value`
- Operators
  - `T enumflags::operator~(T)`
  - `T enumflags::operator&(T, T)`
  - `T enumflags::operator|(T, T)`
  - `T enumflags::operator^(T, T)`
  - `T& enumflags::operator&=(T&, T)`
  - `T& enumflags::operator|=(T&, T)`
  - `T& enumflags::operator^=(T&, T)`
- Functions
  - `bool enumflags::has_exact_flags(T, T)`
  - `bool enumflags::has_any_flags(T, T)`
  - `T enumflags::set_flags(T, T)`
  - `T enumflags::unset_flags(T, T)`
  - `T enumflags::toggle_flags(T, T)`

Example
=======

The 8086 processor's status register may be represented as follows:

```cpp
#include <enumflags.hpp>
#include <cstdint>

enum class status_register : std::uint16_t {
    carry = 1 << 0,
    parity = 1 << 2,
    adjust = 1 << 4,
    zero = 1 << 6,
    sign = 1 << 7,
    trap = 1 << 8,
    interrupt = 1 << 9,
    direction =  1 << 10,
    overflow = 1 << 11,
};

template <>
struct enumflags::has_flags_attribute<status_register> {
    static constexpr bool value{true};
};
```

One might use this flag type as follows:

```cpp
#include "status_register.hpp"

using namespace enumflags;

// ...
auto flags = flag_none<status_register>::value;
// ...
flags = set_flags(flags, status_register::carry);
// ...
if (has_exact_flags(flags, status_register::carry)) {
    // ...
}
/// ...
```
