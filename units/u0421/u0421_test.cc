// FILE: u0421_test.cc
#include "gtest/gtest.h"
#include "ceres/suitesparse.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0421, PathP1) {
  void * arg_0 = nullptr;
  ceres::internal::SuiteSparse target(arg_0);
  target.Free(nullptr);
}
