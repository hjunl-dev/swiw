#pragma once
#include <src/platform/concurrent/bq.h>


namespace swiw::platform::concurrent
{
	template<typename T>
	class ArrayBQ : public BQ<T>
	{
	public:
		ArrayBQ() = default;
		~ArrayBQ() = default;

	public:
		void Push(const T& item) override {}
		void Push(T&& item) override {}
		T Pop() override {}
		std::optional<T> Poll(std::chrono::milliseconds timeout) override {}
		size_t DrainTo(std::vector<T>& outVec) override {}
		bool Shutdown() override {}
		size_t Size() override {}
		size_t Capacity() override {}
	};
}
