// FILE: u0913_test.cc
#include "gtest/gtest.h"
#include "ceres/thread_pool.h"

// P1: START -> 1 -> END
TEST(MaxNumThreadsAvailableTest, TC1_CallsTarget) {
  ThreadPool object{};
  object.MaxNumThreadsAvailable();
}

// P2: START -> 1 -> END
TEST(MaxNumThreadsAvailableTest, TC2_CallsTarget) {
  ThreadPool object{};
  object.MaxNumThreadsAvailable();
}

