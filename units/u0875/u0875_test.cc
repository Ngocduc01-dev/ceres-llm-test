// FILE: u0875_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_vector_ops.h"

// P1: START -> 1 -> END
TEST(ParallelSetZeroTest, TC1_CallsTarget) {
  int a1 = 0;
  VectorType& vector a2{};
  ceres::internal::ParallelSetZero(nullptr, a1, a2);
}

