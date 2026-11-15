// FILE: u0276_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0276, PathP1) {
  ceres::internal::DenseCholesky* object = nullptr;
  object->~DenseCholesky();
}
