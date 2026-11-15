// FILE: u1433_test.cc
#include "gtest/gtest.h"
#include "ceres/thread_pool.h"

// P1: START -> 1 -> END
TEST(u1433_Test, TC1_CallsTarget) {
  ceres::internal::ThreadPool target{};
}
