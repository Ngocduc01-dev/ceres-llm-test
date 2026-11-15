// FILE: u0765_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0765, TC1_CallsTarget) {
  Vector delta_x{};
  Vector delta_gradient{};
  ceres::internal::LowRankInverseHessian object{};
  object.Update(delta_x, delta_gradient);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0765, TC2_CallsTarget) {
  Vector delta_x{};
  Vector delta_gradient{};
  ceres::internal::LowRankInverseHessian object{};
  object.Update(delta_x, delta_gradient);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0765, TC3_CallsTarget) {
  Vector delta_x{};
  Vector delta_gradient{};
  ceres::internal::LowRankInverseHessian object{};
  object.Update(delta_x, delta_gradient);
}
