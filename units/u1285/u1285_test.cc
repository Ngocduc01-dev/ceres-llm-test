// FILE: u1285_test.cc
#include "gtest/gtest.h"
#include "ceres/cgnr_solver.h"
#include "ceres/linear_operator.h"
#include "ceres/parallel_vector_ops.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1285, TC1_CallsTarget) {
  Vector x{};
  Vector y{};
  ceres::internal::CgnrLinearOperator object{};
  object.RightMultiplyAndAccumulate(x, y);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1285, TC2_CallsTarget) {
  Vector x{};
  Vector y{};
  ceres::internal::CgnrLinearOperator object{};
  object.RightMultiplyAndAccumulate(x, y);
}
