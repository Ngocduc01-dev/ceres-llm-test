// FILE: u1003_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/partitioned_matrix_view.h"

// P1: START -> 1 -> END
TEST(BackSubstituteTest, TC1_CallsTarget) {
  ImplicitSchurComplement object{};
  double a0[5] = {};
  double a1[5] = {};
  object.BackSubstitute(a0, a1);
}

