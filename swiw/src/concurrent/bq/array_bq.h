#pragma once
#include <src/concurrent/bq.h>

#include <mutex>
#include <atomic>
#include <queue>
#include <condition_variable>


namespace swiw::concurrent
{
	namespace detail
	{
		template<typename T>
		struct ArrayBQState
		{
			std::queue<T> buf_;
			std::mutex bq_mutex_;
			std::condition_variable full_check_;
			std::condition_variable empty_check_;
			std::atomic_bool shutdown_;
			size_t capacity_;

			ArrayBQState(size_t capacity) : capacity_(capacity), shutdown_(false)
			{
				buf_.reserve(capacity_);
			}
		};
	}

	template<typename T>
	class ArrayBQ : public BQ<T>
	{
	public:
		ArrayBQ() = default;
		~ArrayBQ() = default;

	public:
		void Push(const T& item) override
		{
			std::unique_lock<std::mutex> lock(bq_mutex_);

			state_.full_check_.wait(lock, [this]
				{
					return FullCheckPredicate();
				});

			if (state_.shutdown_)
				throw BQException("Queue is shutdown");

			auto was_empty = state_.buf_.empty();
			state_.buf_.push(item);
			if (was_empty)
				state_.empty_check_.notify_one();
		}

		void Push(T&& item) override
		{
			std::unique_lock<std::mutex> lock(bq_mutex_);

			state_.full_check_.wait(lock, [this]
				{
					return FullCheckPredicate();
				});

			if (state_.shutdown_)
				throw BQException("Queue is shutdown");

			auto was_empty = state_.buf_.empty();
			state_.buf_.push(std::move(item));
			if (was_empty)
				state_.empty_check_.notify_one();
		}

		T Pop() override
		{
			std::unique_lock<std::mutex> lock(bq_mutex_);

			state_.empty_check_.wait(lock, [this]
				{
					return EmptyCheckPredicate();
				});

			if (state_.shutdown_ && state_.buf_.empty())
				throw BQException("Queue is shutdown and empty");

			auto was_full = state_.buf_.size() == state_.capacity_;
			auto item = std::move(state_.buf_.front());
			state_.buf_.pop();

			if (was_full)
				state_.full_check_.notify_one();
			return item;
		}

		std::optional<T> Poll(std::chrono::milliseconds timeout) override
		{
			std::unique_lock<std::mutex> lock(bq_mutex_);

			bool timeout = !state_.empty_check_.wait_for(lock, timeout, [this]
				{
					return EmptyCheckPredicate();
				});

			if (timeout)
				return std::nullopt;
			if (state_.shutdown_ && state_.buf_.empty())
				return std::nullopt;

			auto was_full = state_.buf_.size() == state_.capacity_;
			auto item = std::move(state_.buf_.front());
			state_.buf_.pop();

			if (was_full)
				state_.full_check_.notify_one();
			return item;
		}

		size_t DrainTo(std::vector<T>& outVec) override
		{
			std::lock_guard<std::mutex> lock(bq_mutex_);
			size_t count = state_.buf_.size();

			while (!state_.buf_.empty())
			{
				outVec.push_back(std::move(state_.buf_.begin());
				state_.buf_.pop();
			}

			if (count > 0)
				state_.full_check_.notify_all();
			return count;
		}

		bool Shutdown() override
		{
			if (!state_.shutdown_.load(std::memory_order_acquire))
			{
				state_.shutdown_.store(true, std::memory_order_release);
				state_.full_check_.notify_all();
				state_.empty_check_.notify_all();
			}
		}

		size_t Size() override
		{
			std::lock_guard<std::mutex> lock(bq_mutex_);
			return buf_.size();
		}

		size_t Capacity() override
		{
			return state_.capacity_;
		}

	private:
		bool FullCheckPredicate()
		{
			return state_.buf_.size() < state_.capacity_ || state_.shutdown_;
		}

		bool EmptyCheckPredicate()
		{
			return state_.buf_.empty() || state_.shutdown_;
		}

	private:
		detail::ArrayBQState<T> state_;
	};
} // namespace swiw::concurrent
