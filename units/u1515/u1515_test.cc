// FILE: u1515_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/linear_solver.h"
#include "ceres/preconditioner.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1515_Test, TC1_CallsTarget) {
  ceres::internal::VisibilityBasedPreconditioner target{};
}
