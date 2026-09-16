#pragma once
#include <atomic>

namespace swiw::async {

// ============================================================
// std::condition_variable waiter count for optimize Blocking Queue
// ============================================================

using Waiters = std::atomic_size_t;

class [[nodiscard]] WaiterGuard {
 public:
  explicit WaiterGuard(Waiters& w) noexcept : w_(w) {
    w_.fetch_add(1, std::memory_order_relaxed);
  }
  WaiterGuard(const WaiterGuard&) = delete;
  WaiterGuard(WaiterGuard&&) = delete;

  ~WaiterGuard() { w_.fetch_sub(1, std::memory_order_relaxed); }

 private:
  Waiters& w_;
};

class CondWaiters {
 public:
  constexpr CondWaiters() noexcept = default;

  [[nodiscard]] WaiterGuard Enter() noexcept { return WaiterGuard(w_); }
  [[nodiscard]] bool Any() const noexcept {
    return w_.load(std::memory_order_relaxed);
  }
  [[nodiscard]] std::size_t Count() const noexcept {
    return w_.load(std::memory_order_relaxed);
  }

 private:
  Waiters w_{0};
};
}  // namespace swiw::async
