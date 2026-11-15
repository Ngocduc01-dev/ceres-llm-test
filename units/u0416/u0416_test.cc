// FILE: u0416_test.cc
#include "gtest/gtest.h"
#include "ceres/sparse_normal_cholesky_solver.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0416, PathP1) {
  { ceres::internal::SparseNormalCholeskySolver target; }
}
