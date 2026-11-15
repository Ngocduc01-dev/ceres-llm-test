// FILE: u1080_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

// P1: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC1_CallsTarget) {
  SparseMatrixPreconditionerWrapper object{};
  double a0[5] = {};
  double a1[5] = {};
  object.RightMultiplyAndAccumulate(a0, a1);
}

