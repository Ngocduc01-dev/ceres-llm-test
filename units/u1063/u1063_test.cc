// FILE: u1063_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/partitioned_matrix_view.h"

// P1: START -> 1 -> END
TEST(UpdateRhsTest, TC1_CallsTarget) {
  ImplicitSchurComplement object{};
  object.UpdateRhs();
}

