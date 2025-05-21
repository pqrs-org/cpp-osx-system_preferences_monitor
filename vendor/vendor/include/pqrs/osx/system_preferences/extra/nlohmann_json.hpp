#pragma once

// (C) Copyright Takayama Fumihiko 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See http://www.boost.org/LICENSE_1_0.txt)

#include <pqrs/hid/extra/nlohmann_json.hpp>
#include <pqrs/json.hpp>
#include <pqrs/osx/iokit_types/extra/nlohmann_json.hpp>
#include <pqrs/osx/system_preferences/keyboard_type_key.hpp>
#include <pqrs/osx/system_preferences/properties.hpp>

namespace pqrs {
namespace osx {
namespace system_preferences {

// keyboard_type_key

inline void to_json(nlohmann::json& j, const keyboard_type_key& value) {
  j = nlohmann::json::object({
      {"vendor_id", value.get_vendor_id()},
      {"product_id", value.get_product_id()},
      {"country_code", value.get_country_code()},
  });
}

inline void from_json(const nlohmann::json& j, keyboard_type_key& value) {
  using namespace std::string_literals;

  json::requires_object(j, "json");

  for (const auto& [k, v] : j.items()) {
    if (k == "vendor_id") {
      try {
        value.set_vendor_id(v.get<hid::vendor_id::value_t>());
      } catch (json::unmarshal_error& e) {
        throw json::unmarshal_error(k + " error: "s + e.what());
      }

    } else if (k == "product_id") {
      try {
        value.set_product_id(v.get<hid::product_id::value_t>());
      } catch (json::unmarshal_error& e) {
        throw json::unmarshal_error(k + " error: "s + e.what());
      }

    } else if (k == "country_code") {
      try {
        value.set_country_code(v.get<hid::country_code::value_t>());
      } catch (json::unmarshal_error& e) {
        throw json::unmarshal_error(k + " error: "s + e.what());
      }

    } else {
      throw json::unmarshal_error("unknown key: `"s + k + "`"s);
    }
  }
}

// properties

inline void to_json(nlohmann::json& j, const properties& value) {
  j = nlohmann::json::object({
      {"use_fkeys_as_standard_function_keys", value.get_use_fkeys_as_standard_function_keys()},
      {"scroll_direction_is_natural", value.get_scroll_direction_is_natural()},
      {"keyboard_types", value.get_keyboard_types()},
  });
}

inline void from_json(const nlohmann::json& j, properties& value) {
  using namespace std::string_literals;

  json::requires_object(j, "json");

  for (const auto& [k, v] : j.items()) {
    if (k == "use_fkeys_as_standard_function_keys") {
      json::requires_boolean(v, "`"s + k + "`");

      value.set_use_fkeys_as_standard_function_keys(v.get<bool>());

    } else if (k == "scroll_direction_is_natural") {
      json::requires_boolean(v, "`"s + k + "`");

      value.set_scroll_direction_is_natural(v.get<bool>());

    } else if (k == "keyboard_types") {
      json::requires_array(v, "`"s + k + "`");

      try {
        value.set_keyboard_types(v.get<std::map<keyboard_type_key, iokit_keyboard_type::value_t>>());
      } catch (std::exception& e) {
        throw json::unmarshal_error("keyboard_types error: "s + e.what());
      }

    } else {
      throw json::unmarshal_error("unknown key: `"s + k + "`"s);
    }
  }
}
} // namespace system_preferences
} // namespace osx
} // namespace pqrs
