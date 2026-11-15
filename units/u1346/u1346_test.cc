// FILE: u1346_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/sparse_normal_cholesky_solver.h"

// P1: START -> 1 -> END
TEST(u1346_Test, TC1_CallsTarget) {
  ceres::internal::SparseNormalCholeskySolver target{};
}
