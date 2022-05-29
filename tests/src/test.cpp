#include <boost/ut.hpp>
#include <pqrs/osx/system_preferences_monitor.hpp>

int main(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "monitor"_test = [] {
    auto time_source = std::make_shared<pqrs::dispatcher::hardware_time_source>();
    auto dispatcher = std::make_shared<pqrs::dispatcher::dispatcher>(time_source);

    auto monitor = std::make_shared<pqrs::osx::system_preferences_monitor>(dispatcher);

    monitor = nullptr;

    dispatcher->terminate();
    dispatcher = nullptr;
  };

  return 0;
}
