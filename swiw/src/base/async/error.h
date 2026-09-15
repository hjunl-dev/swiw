#pragma once
#include "src/base/common/result.h"

namespace swiw::async {

// ============================================================
// Errors for BQ<T>, Executor
// ============================================================

enum class PushError : uint8_t { Disposed, WouldBlock };
enum class PopError : uint8_t { Disposed, WouldBlock };

using PushResult = swiw::common::Result<void, PushError>;

template <typename T>
using PopResult = swiw::common::Result<T, PopError>;

inline const wchar_t* ErrorToString(PushError e) noexcept {
  switch (e) {
    case PushError::Disposed:
      return L"Queue is disposed";
    case PushError::WouldBlock:
      return L"Queue is full";
  }
}

inline const wchar_t* ErrorToString(PopError e) noexcept {
  switch (e) {
    case PopError::Disposed:
      return L"Queue is disposed";
    case PopError::WouldBlock:
      return L"Queue is empty";
  }
}
}  // namespace swiw::async
