#include <csignal>
#include <iostream>
#include <pqrs/osx/system_preferences_monitor.hpp>

namespace {
auto global_wait = pqrs::make_thread_wait();
}

int main(void) {
  std::signal(SIGINT, [](int) {
    global_wait->notify();
  });

  auto time_source = std::make_shared<pqrs::dispatcher::hardware_time_source>();
  auto dispatcher = std::make_shared<pqrs::dispatcher::dispatcher>(time_source);

  auto monitor = std::make_shared<pqrs::osx::system_preferences_monitor>(dispatcher);

  monitor->system_preferences_changed.connect([](auto&& properties_ptr) {
    if (properties_ptr) {
      std::cout << "system_preferences_changed:" << std::endl;

      std::cout << "  use_fkeys_as_standard_function_keys: "
                << properties_ptr->get_use_fkeys_as_standard_function_keys()
                << std::endl;

      std::cout << "  scroll_direction_is_natural: "
                << properties_ptr->get_scroll_direction_is_natural()
                << std::endl;

      std::cout << "  keyboard_types: " << std::endl;
      for (const auto& [k, v] : properties_ptr->get_keyboard_types()) {
        std::cout << "    {" << std::endl;
        std::cout << "      vendor_id: " << k.get_vendor_id() << std::endl;
        std::cout << "      product_id: " << k.get_product_id() << std::endl;
        std::cout << "      country_code: " << k.get_country_code() << std::endl;
        std::cout << "      keyboard_type: " << v << std::endl;
        std::cout << "    }" << std::endl;
      }
    }
  });

  monitor->async_start(std::chrono::milliseconds(1000));

  // ============================================================

  global_wait->wait_notice();

  // ============================================================

  monitor = nullptr;

  dispatcher->terminate();
  dispatcher = nullptr;

  std::cout << "finished" << std::endl;

  return 0;
}
