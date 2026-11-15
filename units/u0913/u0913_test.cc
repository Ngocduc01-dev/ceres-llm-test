// FILE: u0913_test.cc
#include "gtest/gtest.h"
#include "ceres/thread_pool.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0913, TC1_CallsTarget) {
  ceres::internal::ThreadPool object{};
  object.MaxNumThreadsAvailable();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0913, TC2_CallsTarget) {
  ceres::internal::ThreadPool object{};
  object.MaxNumThreadsAvailable();
}
