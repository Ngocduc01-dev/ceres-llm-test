// FILE: u0337_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0337, PathP1) {
  int arg_0 = 1;
  int arg_1 = 1;
  bool arg_2 = true;
  ceres::internal::LowRankInverseHessian target(arg_0, arg_1, arg_2);
  target.LowRankInverseHessian(1, 1, true);
}
