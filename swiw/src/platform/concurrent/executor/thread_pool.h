#pragma once
#include <src/platform/concurrent/executor.h>
#include <src/platform/concurrent/bq.h>

#include <memory>
#include <vector>
#include <atomic>


namespace swiw::platform::concurrent
{
	namespace detail
	{
		struct ThreadPoolState
		{
			std::unique_ptr<BQ<Job>> job_queue_;
			std::atomic_bool accepting_;
			std::atomic_bool running_;
		};
	}

	class ThreadPool : public Executor
	{
	public:
		ThreadPool(size_t worker_count);
		~ThreadPool() override;

	public:
		void Submit(Job&& job) override {}
		void Shutdown() override {}
		std::vector<Job> ShutdownNow() override {}
		bool IsShutdown() const override {}

	private:
		std::shared_ptr<detail::ThreadPoolState> state_;
		std::vector<std::unique_ptr<Worker>> workers_;
	};
}
