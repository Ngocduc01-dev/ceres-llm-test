// FILE: u1032_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/partitioned_matrix_view.h"

// P1: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC1_CallsTarget) {
  ImplicitSchurComplement object{};
  double a0[5] = {};
  double a1[5] = {};
  object.RightMultiplyAndAccumulate(a0, a1);
}

// P2: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC2_CallsTarget) {
  ImplicitSchurComplement object{};
  double a0[5] = {};
  double a1[5] = {};
  object.RightMultiplyAndAccumulate(a0, a1);
}

