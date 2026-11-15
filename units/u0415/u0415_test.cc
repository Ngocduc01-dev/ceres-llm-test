// FILE: u0415_test.cc
#include "gtest/gtest.h"
#include "ceres/sparse_cholesky.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0415, PathP1) {
  { ceres::internal::RefinedSparseCholesky target; }
}
