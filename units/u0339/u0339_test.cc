// FILE: u0339_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0339, PathP1) {
  ceres::internal::LowRankInverseHessian target;
  target.num_cols();
}
