// FILE: u0290_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"

TEST(Unit_u0290, PathP1) {
  // Path P1: START -> 1 -> END.
  ceres::internal::FloatEigenSparseCholesky* object = nullptr;
  object->~FloatEigenSparseCholesky();
}
