#include <atomic>
#include <boost/ut.hpp>
#include <pqrs/osx/system_preferences_monitor.hpp>
#include <thread>

int main() {
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

  "async_trigger_system_preferences_changed"_test = [] {
    auto time_source = std::make_shared<pqrs::dispatcher::hardware_time_source>();
    auto dispatcher = std::make_shared<pqrs::dispatcher::dispatcher>(time_source);

    auto monitor = std::make_shared<pqrs::osx::system_preferences_monitor>(dispatcher);

    std::atomic<bool> called = false;
    std::atomic<bool> dispatcher_thread = false;
    std::atomic<bool> has_properties = false;

    monitor->system_preferences_changed.connect([&](auto&& properties_ptr) {
      has_properties = pqrs::unwrap_not_null(properties_ptr) != nullptr;
      dispatcher_thread = dispatcher->dispatcher_thread();
      called = true;
    });

    monitor->async_trigger_system_preferences_changed();

    for (int i = 0; i < 100 && !called; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    expect(called.load());
    expect(dispatcher_thread.load());
    expect(has_properties.load());

    monitor = nullptr;

    dispatcher->terminate();
    dispatcher = nullptr;
  };

  return 0;
}
