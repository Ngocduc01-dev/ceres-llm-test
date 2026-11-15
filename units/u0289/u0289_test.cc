// FILE: u0289_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"

TEST(Unit_u0289, PathP1) {
  // Path P1: START -> 1 -> END.
  ceres::internal::EigenSparseCholesky* object = nullptr;
  object->~EigenSparseCholesky();
}
