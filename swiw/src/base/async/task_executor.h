#pragma once
#include "base/async/async.h"

namespace swiw::async {
class TaskExecutor final : public Executor {
 public:
  TaskExecutor() {}
  TaskExecutor(const TaskExecutor&) = delete;
  TaskExecutor& operator=(const TaskExecutor&) = delete;
  ~TaskExecutor() {}

  // submit api
  [[nodiscard]] PushResult Submit() override { return PushResult(); }
  [[nodiscard]] PushResult TrySubmit() override { return PushResult(); }

  // misc api
  void Dispose() override {}
  bool IsDisposed() const override { return false; }
  std::size_t Capacity() const override { return 0; }
  std::size_t WorkerSize() const override { return 0; }

 private:
  std::size_t num_workers_{0};
};
}  // namespace swiw::async
