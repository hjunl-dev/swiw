#pragma once
#include <chrono>
#include <format>
#include <iostream>
#include <string>

namespace swiw::common {

// ============================================================
// Timer for measuring interval execution time
// ============================================================

class [[nodiscard]] TimerGuard {
 public:
  using Clock = std::chrono::steady_clock;

  explicit TimerGuard(std::wstring label)
      : label_(std::move(label)), start_(Clock::now()) {}

  ~TimerGuard() {
    const auto elapsed = ElapsedMs();
    try {
      std::wcout << std::format(L"[{}] time elapsed: {:.3f}ms", label_, elapsed)
                 << std::endl;
    } catch (...) {
    }
  }

  TimerGuard(const TimerGuard&) = delete;
  TimerGuard& operator=(const TimerGuard&) = delete;

  [[nodiscard]] Clock::duration Elapsed() const {
    return Clock::now() - start_;
  }
  [[nodiscard]] double ElapsedMs() const { return ElapsedAs(); }
  [[nodiscard]] double ElapsedSec() const { return ElapsedAs<std::ratio<1>>(); }

 private:
  template <typename Unit = std::milli>
  [[nodiscard]] double ElapsedAs() const {
    return std::chrono::duration<double, Unit>(Elapsed()).count();
  }

  std::wstring label_;
  Clock::time_point start_;
};

}  // namespace swiw::common
