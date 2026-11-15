// FILE: u1360_test.cc
#include "gtest/gtest.h"
#include "ceres/thread_pool.h"

// P1: START -> 1 -> END
TEST(u1360_Test, TC1_CallsTarget) {
  ceres::internal::ThreadPool target{};
  target.Resize(nullptr);
}

// P2: START -> 1 -> END
TEST(u1360_Test, TC2_CallsTarget) {
  ceres::internal::ThreadPool target{};
  target.Resize(nullptr);
}

// P3: START -> 1 -> END
TEST(u1360_Test, TC3_CallsTarget) {
  ceres::internal::ThreadPool target{};
  target.Resize(nullptr);
}
