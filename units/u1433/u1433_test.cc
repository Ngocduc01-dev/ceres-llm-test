// FILE: u1433_test.cc
#include "gtest/gtest.h"
#include "ceres/thread_pool.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1433, TC1_CallsTarget) {
  int num_threads{};
  ceres::internal::ThreadPool object{};
  (void)object;
}
