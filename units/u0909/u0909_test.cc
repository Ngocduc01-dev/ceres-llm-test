// FILE: u0909_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_vector_ops.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0909, TC1_CallsTarget) {
  int num_threads{};
  LhsExpression lhs{};
  RhsExpression rhs{};
  ceres::internal::ParallelAssign(nullptr, num_threads, lhs, rhs);
}
