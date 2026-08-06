#pragma once
#include <string>
#include <functional>
#include <exception>


/**
* @brief Executor interface for task execution.
*/
namespace swiw::platform::concurrent
{
	using Job = std::function<void()>;

	class ExecutorException : public std::exception
	{
	public:
		explicit ExecutorException(const char* message) : std::exception(message) {}
		explicit ExecutorException(const std::string& message) : std::exception(message.c_str()) {}
	};

	class WorkerException : public std::exception
	{
	public:
		explicit WorkerException(const char* message) : std::exception(message) {}
		explicit WorkerException(const std::string& message) : std::exception(message.c_str()) {}
	};

	class Executor
	{
	public:
		Executor() = default;
		virtual ~Executor() = default;

	public:
		virtual void Submit(Job&& job) = 0;
		virtual void Shutdown() = 0;
		virtual std::vector<Job> ShutdownNow() = 0;
		virtual bool IsShutdown() const = 0;
	};

	class Worker
	{
	public:
		Worker() = default;
		virtual ~Worker() = default;

	public:
		virtual void Submit(std::function<void()> task) = 0;
		virtual void Shutdown() = 0;
	};
}
