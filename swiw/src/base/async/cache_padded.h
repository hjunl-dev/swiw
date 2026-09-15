#pragma once
#include <type_traits>

namespace swiw::async {

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
}  // namespace swiw::async
