// FILE: u0338_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LowRankInverseHessianNumRowsTest, P1_ReturnsNumParameters) {
  ceres::internal::LowRankInverseHessian hessian(3, 2, true);
  hessian.num_rows();
}
