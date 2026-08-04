#pragma once
#include <optional>
#include <chrono>
#include <vector>
#include <exception>

/**
* @brief Blocking Queue for Producer-Consumer pattern.
* @tparam T The type of items stored in the queue.
*/
namespace swiw::platform::concurrent
{
	class BQException : public std::exception
	{
	public:
		explicit BQException(const char* message) : std::exception(message) {}
		explicit BQException(const std::string& message) : std::exception(message.c_str()) {}
	};

	template<typename T>
	class BQ
	{
	public:
		BQ() = default;
		virtual ~BQ() = default;

	public:
		virtual void Push(const T& item) = 0;
		virtual void Push(T&& item) = 0;
		virtual T Pop() = 0;
		virtual std::optional<T> Poll(std::chrono::milliseconds timeout) = 0;
		virtual size_t DrainTo(std::vector<T>& outVec) = 0;
		virtual bool Shutdown() = 0;
		virtual size_t Size() = 0;
		virtual size_t Capacity() = 0;
	};

} // namespace swiw::platform::concurrent
