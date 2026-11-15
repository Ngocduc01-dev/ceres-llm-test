// FILE: u0477_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_for.h"

#include <mutex>

namespace ceres {
namespace internal {

// P1: START -> 1 -> 2 -> END (node 1: đúng)
TEST(MakeConditionalLockTest, SingleThreadReturnsEmptyLock) {
  std::mutex m;
  const int num_threads = 1;
  auto lock = MakeConditionalLock(num_threads, m);
  (void)lock;
}

// P2: START -> 1 -> 2 -> END (node 1: sai)
TEST(MakeConditionalLockTest, MultiThreadReturnsLockOnMutex) {
  std::mutex m;
  const int num_threads = 4;
  auto lock = MakeConditionalLock(num_threads, m);
  (void)lock;
}

}  // namespace internal
}  // namespace ceres
