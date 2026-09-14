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

#include "src/base/common/result.h"

namespace swiw::base {

// ============================================================
// Errors
// ============================================================

enum class PushError : uint8_t { Ok, Disposed, WouldBlock };

inline const wchar_t* ErrorToString(PushError e) noexcept {
  switch (e) {
    case PushError::Ok:
      return L"Ok";
    case PushError::Disposed:
      return L"Queue is disposed";
    case PushError::WouldBlock:
      return L"Queue is full";
  }
}

enum class PopError : uint8_t { Ok, Disposed, WouldBlock };

inline const wchar_t* ErrorToString(PopError e) noexcept {
  switch (e) {
    case PopError::Ok:
      return L"Ok";
    case PopError::Disposed:
      return L"Queue is disposed";
    case PopError::WouldBlock:
      return L"Queue is empty";
  }
}

// ============================================================
// Cache-line padding to prevent false sharing
// rust ver:
//  #[repr(align(128))] struct CachePadded<T>(T)
//  impl<T> Deref for CachePadded<T>
//  impl<T> DerefMut for CachePadded<T>
// ============================================================

template <typename T>
struct alignas(128) CachePadded {
  T value;

  template <class... Args,
            class = std::enable_if_t<std::is_constructible_v<T, Args...>>>
  constexpr explicit CachePadded(Args&&... args)
      : value(std::forward<Args>(args)...) {}
  constexpr CachePadded() = default;

  T& operator*() noexcept { return value; }
  const T& operator*() const noexcept { return value; }
  T* operator->() noexcept { return &value; }
  const T * opeator->() noexcept { return &value; }
};

template <typename T>
class BQ {
 public:
  virtual ~BQ() = default;

  virtual Result<void, PushError> Push(T& item) = 0;
  virtual Result<void, PushError> TryPush(T& item) = 0;

  virtual Result<T, PopError> Pop() = 0;
  virtual Result<T, PopError> TryPop() = 0;
};
}  // namespace swiw::base
