#pragma once
#include <optional>
#include <type_traits>
#include <variant>

namespace swiw::base {

// ============================================================
// Err
// ============================================================
template <typename E>
struct Err {
  E err;
};
template <typename E>
Err(E) -> Err<E>;

// ============================================================
// Result
//
// like Rust Result<T, E> , std::expected<T, E> (cxx23)
// ============================================================

template <typename T, typename E>
class [[nodiscard]] Result {
 public:
  Result(T value) : v_(std::in_place_index<0>, std::move(value)) {}

  template <typename G>
    requires std::constructible_from<E, G>
  Result(Err<G> e) : v_(std::in_place_index<1>, std::move(e.error)) {}

  bool IsOk() const noexcept { return v_.index() == 0; }
  bool IsErr() const noexcept { return v_.index() == 1; }
  explicit operator bool() const noexcept { return IsOk(); }

  T& Value() & { return std::get<0>(v_); }
  const T& Value() const& { return std::get<0>(v_); }
  T Value() && { return std::get<0>(std::move(v_)); }

  E& Error() & { return std::get<1>(v_); }
  const E& Error() const& { return std::get<1>(v_); }
  E Error() && { return std::get<1>(std::move(v_)); }

  T* IfOk() & noexcept { return std::get_if<0>(&v_); }
  const T* IfOk() const& noexcept { return std::get_if<0>(&v_); }
  T* IfOk() && = delete;

  E* IfErr() & noexcept { return std::get_if<1>(&v_); }
  const E* IfErr() const& noexcept { return std::get_if<1>(&v_); }
  E* IfErr() && = delete;

 private:
  std::variant<T, E> v_;
};

template <typename E>
class [[nodiscard]] Result<void, E> {
 public:
  Result() noexcept = default;

  template <typename G>
    requires std::constructible_from<E, G>
  Result(Err<G> e) : err_(std::in_place, std::move(e.error)) {}

  bool IsOk() const noexcept { return !err_.has_value(); }
  bool IsErr() const noexcept { return err_.has_value(); }
  explicit operator bool() const noexcept { return IsOk(); }

  E& Error() & { return err_.value(); }
  const E& Error() const& { return err_.value(); }
  E Error() && { return std::move(err_).value(); }

  E* IfErr() & noexcept { return err_.has_value() ? &*err_ : nullptr; }
  const E* IfErr() const& noexcept {
    return err_.has_value() ? &*err_ : nullptr;
  }
  E* IfErr() && = delete;

 private:
  std::optional<E> err_;
};

}  // namespace swiw::base
