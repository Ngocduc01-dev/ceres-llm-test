// FILE: u1073_test.cc
#include "gtest/gtest.h"
#include "ceres/conjugate_gradients_solver.h"
#include "ceres/linear_operator.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1073, TC1_CallsTarget) {
  Vector x{};
  Vector y{};
  ceres::internal::LinearOperatorAdapter object{};
  object.RightMultiplyAndAccumulate(x, y);
}
