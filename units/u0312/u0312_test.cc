// FILE: u0312_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/partitioned_matrix_view.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0312, PathP1) {
  ceres::internal::ImplicitSchurComplement target;
  target.num_rows();
}
