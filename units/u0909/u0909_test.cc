// FILE: u0909_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/parallel_vector_ops.h"

// P1: START -> 1 -> END
TEST(ParallelAssignTest, TC1_CallsTarget) {
  int a1 = 0;
  LhsExpression& lhs a2{};
  RhsExpression& rhs a3{};
  ceres::internal::ParallelAssign(nullptr, a1, a2, a3);
}

