// FILE: u0490_test.cc
#include "gtest/gtest.h"
#include "ceres/concurrent_queue.h"
#include "ceres/thread_token_provider.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC1_ZeroThreads) {
  ThreadTokenProvider provider(0);
}

// P2: START -> 1 -> 2(đúng) -> 3 -> 4 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC2_OneThread) {
  ThreadTokenProvider provider(1);
}

// P3: START -> 1 -> (2(đúng) -> 3 -> 4) x2 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC3_TwoThreads) {
  ThreadTokenProvider provider(2);
}

// P4: START -> 1 -> (2(đúng) -> 3 -> 4) x3 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC4_ThreeThreads) {
  ThreadTokenProvider provider(3);
}

// P5: START -> 1 -> (2(đúng) -> 3 -> 4) x4 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC5_FourThreads) {
  ThreadTokenProvider provider(4);
}

// P6: START -> 1 -> (2(đúng) -> 3 -> 4) x5 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC6_FiveThreads) {
  ThreadTokenProvider provider(5);
}

// P7: START -> 1 -> (2(đúng) -> 3 -> 4) x6 -> 2(sai) -> END
TEST(ThreadTokenProviderCtorTest, TC7_SixThreads) {
  ThreadTokenProvider provider(6);
}

}  // namespace internal
}  // namespace ceres
