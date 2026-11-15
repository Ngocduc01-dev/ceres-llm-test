// FILE: u1009_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1009, TC1_CallsTarget) {
  ceres::internal::LowRankInverseHessian object{};
  object.LeftMultiplyAndAccumulate(nullptr, nullptr);
}
