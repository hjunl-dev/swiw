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
