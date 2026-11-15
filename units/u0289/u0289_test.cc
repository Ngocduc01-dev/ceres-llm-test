// FILE: u0289_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0289, PathP1) {
  ceres::internal::EigenSparseCholesky* object = nullptr;
  object->~EigenSparseCholesky();
}
