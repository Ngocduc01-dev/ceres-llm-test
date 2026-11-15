// FILE: u0276_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"

TEST(Unit_u0276, PathP1) {
  // Path P1: START -> 1 -> END.
  ceres::internal::DenseCholesky* object = nullptr;
  object->~DenseCholesky();
}
