#pragma once

// (C) Copyright Takayama Fumihiko 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See http://www.boost.org/LICENSE_1_0.txt)

#include <pqrs/osx/system_preferences/keyboard_type.hpp>

namespace pqrs {
namespace osx {
namespace system_preferences {
inline std::size_t hash_value(const keyboard_type& value) {
  return std::hash<keyboard_type>{}(value);
}
} // namespace system_preferences
} // namespace osx
} // namespace pqrs
