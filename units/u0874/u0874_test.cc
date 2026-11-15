// FILE: u0874_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END
TEST(ParallelSetZeroTest, TC1_CallsTarget) {
  int a1 = 0;
  double a2[5] = {};
  int a3 = 0;
  ceres::internal::ParallelSetZero(nullptr, a1, a2, a3);
}

