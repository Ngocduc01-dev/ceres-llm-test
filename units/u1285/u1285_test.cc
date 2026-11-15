// FILE: u1285_test.cc
#include "gtest/gtest.h"
#include "ceres/cgnr_solver.h"
#include "ceres/linear_operator.h"
#include "ceres/parallel_vector_ops.h"

// P1: START -> 1 -> END
TEST(u1285_Test, TC1_CallsTarget) {
  ceres::internal::CgnrLinearOperator target{};
  target.RightMultiplyAndAccumulate(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1285_Test, TC2_CallsTarget) {
  ceres::internal::CgnrLinearOperator target{};
  target.RightMultiplyAndAccumulate(nullptr, nullptr);
}
