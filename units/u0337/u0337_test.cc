// FILE: u0337_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LowRankInverseHessianConstructorTest, TC1_SinglePath) {
  const int num_parameters = 4;          // khoảng 1..5
  const int max_num_corrections = 3;     // khoảng 1..5
  const bool use_approximate_eigenvalue_scaling = true;
  ceres::internal::LowRankInverseHessian hessian(
      num_parameters, max_num_corrections, use_approximate_eigenvalue_scaling);
  (void)hessian;
}
