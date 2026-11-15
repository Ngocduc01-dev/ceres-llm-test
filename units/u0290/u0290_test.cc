// FILE: u0290_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0290, PathP1) {
  ceres::internal::FloatEigenSparseCholesky* object = nullptr;
  object->~FloatEigenSparseCholesky();
}
