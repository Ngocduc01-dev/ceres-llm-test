// FILE: u0277_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0277, PathP1) {
  // Scope exit invokes ~RefinedDenseCholesky().
  ceres::internal::RefinedDenseCholesky object(nullptr, nullptr);
}
