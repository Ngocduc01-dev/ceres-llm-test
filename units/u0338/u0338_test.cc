// FILE: u0338_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0338, PathP1) { ceres::internal::LowRankInverseHessian target(1, 1, true); target.num_rows(); }
