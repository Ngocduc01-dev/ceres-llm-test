// FILE: u0277_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"

TEST(Unit_u0277, PathP1) {
  // Path P1: START -> 1 -> END.
  // Scope exit invokes ~RefinedDenseCholesky().
  ceres::internal::RefinedDenseCholesky object(nullptr, nullptr);
}
