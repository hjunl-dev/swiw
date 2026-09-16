#pragma once
#include "base/async/async.h"

namespace swiw::async {

template <typename T>
class LinkedBQ final : public BQ<T> {
 public:
  LinkedBQ() {}
  LinkedBQ(const LinkedBQ&) = delete;
  LinkedBQ& operator=(const LinkedBQ&) = delete;
  ~LinkedBQ() {}

  // push api
  [[nodiscard]] PushResult Push(T& item) override { return PushResult(); }
  [[nodiscard]] PushResult TryPush(T& item) override { return PushResult(); }

  // pop api
  [[nodiscard]] PopResult<T> Pop() override { return PopResult<T>(T{}); }
  [[nodiscard]] PopResult<T> TryPop() override { return PopResult<T>(T{}); }

  // misc api
  void Dispose() {}
  bool IsDisposed() const override { return false; }
  std::size_t Capacity() const override { return 0; }
  std::size_t Size() const override { return 0; }

 private:
  std::size_t capacity_{0};
};
}  // namespace swiw::async
