#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <pqrs/osx/system_preferences_monitor.hpp>

TEST_CASE("monitor") {
  auto time_source = std::make_shared<pqrs::dispatcher::hardware_time_source>();
  auto dispatcher = std::make_shared<pqrs::dispatcher::dispatcher>(time_source);

  auto monitor = std::make_shared<pqrs::osx::system_preferences_monitor>(dispatcher);

  monitor = nullptr;

  dispatcher->terminate();
  dispatcher = nullptr;
}
