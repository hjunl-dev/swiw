#pragma once
#include <new>

namespace swiw::common {

// ============================================================
// NoDestructor<T> — the pattern referenced by WorkerPool::leak()
// (like chromium,abseil NoDestructor, folly::Indestructible)
// ============================================================

template <typename T>
class NoDestructor {
 public:
  template <typename... Args>
  explicit NoDestructor(Args&&... args) {
    ::new (static_cast<void*>(storage_)) T(std::forward<Args>(args)...);
  }
  NoDestructor(const NoDestructor&) = delete;
  NoDestructor& operator=(const NoDestructor&) = delete;

  ~NoDestructor() = default;

  T* Get() noexcept { return std::launder(reinterpret_cast<T*>(storage_)); }
  T& operator*() noexcept { return *Get(); }
  T* operator->() noexcept { return Get(); }

 private:
  alignas(T) unsigned char inner_[sizeof(T)];
};

}  // namespace swiw::common
