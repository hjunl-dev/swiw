#pragma once
#include <optional>
#include <chrono>
#include <vector>
#include <exception>

/**
* @brief Blocking Queue for Producer-Consumer pattern.
* @tparam T The type of items stored in the queue.
*/
namespace swiw::concurrent
{
	inline constexpr std::size_t kCacheLineAlign = 128;

	template <class T>
	class alignas(kCacheLineAlign) CachePadded {
	public:
		constexpr CachePadded() noexcept(std::is_nothrow_default_constructible_v<T>) = default;

		constexpr explicit CachePadded(T value) noexcept(std::is_nothrow_move_constructible_v<T>)
			: value_(std::move(value)) {
		}

		[[nodiscard]] constexpr const T& operator*() const noexcept { return value_; }
		[[nodiscard]] constexpr const T* operator->() const noexcept { return &value_; }
		[[nodiscard]] constexpr T& operator*() noexcept { return value_; }
		[[nodiscard]] constexpr T* operator->() noexcept { return &value_; }

		[[nodiscard]] constexpr const T& get() const noexcept { return value_; }
		[[nodiscard]] constexpr T& get() noexcept { return value_; }

	private:
		T value_{};
	};

	static_assert(sizeof(CachePadded<std::atomic<std::size_t>>) == kCacheLineAlign,
		"alignas 는 sizeof 도 alignof 의 배수로 올림합니다(= Rust repr(align) 과 동일).");

	template<typename T>
	class BQ
	{
	public:
		virtual ~BQ() = default;
		virtual void Push(const T& item) = 0;
		virtual void Push(T&& item) = 0;
		virtual T Pop() = 0;
		virtual std::optional<T> Poll(std::chrono::milliseconds timeout) = 0;
		virtual size_t DrainTo(std::vector<T>& outVec) = 0;
		virtual bool Shutdown() = 0;
		virtual size_t Size() = 0;
		virtual size_t Capacity() = 0;
	};
} // namespace swiw::concurrent
