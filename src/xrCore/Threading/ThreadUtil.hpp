#pragma once

#include <functional>
#include <thread>
#include <utility>

#include "Common/types.hpp"
#include "xrCore/cpu.hpp"

namespace Threading {
enum class priority_class {
  idle,
  below_normal,
  normal,
  above_normal,
  high,
  realtime,
};

enum class priority_level {
  idle,
  lowest,
  below_normal,
  normal,
  above_normal,
  highest,
  time_critical,
};

priority_level GetCurrentThreadPriorityLevel();
priority_class GetCurrentProcessPriorityClass();

void SetCurrentThreadPriorityLevel(priority_level prio);
void SetCurrentProcessPriorityClass(priority_class cls);

void SetCurrentThreadName(cpcstr name);

template <typename Invocable, typename... Args>
[[nodiscard]] std::thread RunThread(cpcstr name,
                                    Invocable&& invocable,
                                    Args&&... args) {
  return std::move(std::thread{
      [name](Invocable&& invocable2, Args&&... args2) {
        SetCurrentThreadName(name);
        _initialize_cpu_thread();
        std::invoke(std::move(invocable2), std::move(args2)...);
      },
      std::forward<Invocable>(invocable), std::forward<Args>(args)...});
}

template <typename... Args>
void SpawnThread(Args&&... args) {
  RunThread(std::forward<Args>(args)...).detach();
}
}  // namespace Threading
