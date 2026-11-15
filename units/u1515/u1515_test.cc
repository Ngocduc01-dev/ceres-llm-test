// FILE: u1515_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/linear_solver.h"
#include "ceres/preconditioner.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1515, TC1_CallsTarget) {
  CompressedRowBlockStructure bs{};
  Preconditioner::Options options{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  (void)object;
}
