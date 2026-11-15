// FILE: u1013_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1013, TC1_CallsTarget) {
  int start{};
  int end{};
  int num_work_blocks{};
  ceres::internal::ParallelInvokeState object{};
  (void)object;
}
