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

#include "base/async/error.h"

namespace swiw::async {

template <typename T>
class BQ {
 public:
  virtual ~BQ() = default;

  // push api
  [[nodiscard]] virtual PushResult Push(T& item) = 0;
  [[nodiscard]] virtual PushResult TryPush(T& item) = 0;

  // pop api
  [[nodiscard]] virtual PopResult<T> Pop() = 0;
  [[nodiscard]] virtual PopResult<T> TryPop() = 0;

  // misc api
  virtual void Dispose() = 0;
  virtual bool IsDisposed() const = 0;
  virtual std::size_t Capacity() const = 0;
  virtual std::size_t Size() const = 0;

  // api for r-value reference
  [[nodiscard]] virtual PushResult Push(T&& item) { return Push(item); }
  [[nodiscard]] virtual PushResult TryPush(T&& item) { return TryPush(item); }
};

class Executor {
 public:
  virtual ~Executor() = default;

  // submit api
  [[nodiscard]] virtual PushResult Submit() = 0;
  [[nodiscard]] virtual PushResult TrySubmit() = 0;
  // misc api
  virtual void Dispose() = 0;
  virtual bool IsDisposed() const = 0;
  virtual std::size_t Capacity() const = 0;
  virtual std::size_t WorkerSize() const = 0;
};
}  // namespace swiw::async
