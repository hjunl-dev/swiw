#pragma once
#include "base/async/task_executor.h"

namespace swiw::ffi {

class Runtime {
 public:
  Runtime() = default;
  ~Runtime() = default;

  static Runtime& Instance() {
    static Runtime instance;
    return instance;
  }

  swiw::async::TaskExecutor& Executor() { return executor_; }

 private:
  swiw::async::TaskExecutor executor_;
};
}  // namespace swiw::ffi
