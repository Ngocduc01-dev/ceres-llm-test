// FILE: u1073_test.cc
#include "gtest/gtest.h"
#include "ceres/conjugate_gradients_solver.h"
#include "ceres/linear_operator.h"

// P1: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC1_CallsTarget) {
  LinearOperatorAdapter object{};
  Vector & x a0{};
  Vector & y a1{};
  object.RightMultiplyAndAccumulate(a0, a1);
}

