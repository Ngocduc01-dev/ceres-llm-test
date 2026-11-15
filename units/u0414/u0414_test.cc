// FILE: u0414_test.cc
#include "gtest/gtest.h"
#include "ceres/sparse_cholesky.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0414, PathP1) {
  { ceres::internal::SparseCholesky target; }
}
