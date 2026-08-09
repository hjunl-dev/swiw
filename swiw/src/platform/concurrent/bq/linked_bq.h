#pragma once
#include <src/platform/concurrent/bq.h>

#include <mutex>
#include <atomic>
#include <vector>
#include <condition_variable>


namespace swiw::platform::concurrent
{
	namespace detail
	{
		template<typename T>
		struct LinkedBQState
		{

		};
	}

	template<typename T>
	class LinkedBQ : public BQ<T>
	{
	public:
		LinkedBQ()
		{
		}
		~LinkedBQ()
		{
		}

	public:
		void Push(const T& item) override {}
		void Push(T&& item) override {}
		T Pop() override {}
		std::optional<T> Poll(std::chrono::milliseconds timeout) override {}
		size_t DrainTo(std::vector<T>& outVec) override {}
		bool Shutdown() override {}
		size_t Size() override {}
		size_t Capacity() override {}

	private:
		detail::LinkedBQState<T> state_;
	};
} // namespace swiw::platform::concurrent
