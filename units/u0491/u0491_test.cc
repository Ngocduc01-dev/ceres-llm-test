// FILE: u0491_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"
#include "ceres/thread_token_provider.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> 2 (CHECK đúng) -> END
TEST(ThreadTokenProviderAcquire, TC1_AcquireWithAvailableToken) {
  ThreadTokenProvider provider(3);
  provider.Acquire();
}

}  // namespace internal
}  // namespace ceres
