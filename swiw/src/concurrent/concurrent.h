/*
 * file: concurrent.h
 * Simple concurrent implementation based on hio (rust)
 */
#pragma once

#include <atomic>
#include <chrono>
#include <memory>
#include <string>
#include <type_traits>

namespace swiw::concurrent {
// ============================================================
// Errors
// ============================================================

enum class PushError : uint8_t { Ok, Disposed, WouldBlock };
enum class PopError : uint8_t { Ok, Disposed, WouldBlock };

// ============================================================
// Cache-line padding to prevent false sharing
// rust ver:
//  #[repr(align(128))] struct CachePadded<T>(T)
//      impl<T> Deref / DerefMut for CachePadded<T>
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
}  // namespace swiw::concurrent
