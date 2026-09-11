#pragma once
#include <variant>

namespace swiw::base {

// ============================================================
//  Err
// ============================================================
template <typename E>
struct Err {
  E err;
};

// ============================================================
//  Result
// ============================================================

template <typename T, typename E>
class [[nodiscard]] Result {
 public:
  Result(T value)
      : v_(std::in_place_index<0>, std::move(value)) {}  // Ok(value)

  template <typename TErr>
    requires std::constructible_from<E, TErr>
  Result(Err<TErr> e)
      : v_(std::in_place_index<1>, std::move(e.error)) {}  // Err(e)

  bool IsOk() const noexcept { return v_.index == 0; }
  bool IsErr() const noexcept { return v_.index == 1; }
  explicit operator bool() noexcept { return IsOk(); }

  T& Unwrap() & { return std::get<0>(v_); }
  T&& Unwrap() && { return std::get<0>(std::move(v_)); }
  E& Error() & { return std::get<1>(v_); }
  T&& Error() && { return std::get<1>(std::move(v_)); }

 private:
  std::variant<T, E> v_;
};

}  // namespace swiw::base
