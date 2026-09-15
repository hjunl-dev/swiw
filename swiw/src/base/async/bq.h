/*
 * file: async.h
 * Simple async implementation based on hio (rust) (concurrent)
 */
#pragma once

#include <atomic>
#include <chrono>
#include <memory>
#include <string>
#include <type_traits>

#include "src/base/async/error.h"

namespace swiw::async {

template <typename T>
class BQ {
 public:
  virtual ~BQ() = default;

  [[nodiscard]] virtual PushResult<void> Push(T& item) = 0;
  [[nodiscard]] virtual PushResult<void> TryPush(T& item) = 0;

  [[nodiscard]] virtual PopResult<T> Pop() = 0;
  [[nodiscard]] virtual PopResult<T> TryPop() = 0;
};
}  // namespace swiw::async
