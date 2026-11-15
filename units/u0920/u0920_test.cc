// FILE: u0920_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0920, TC1_CallsTarget) {
  const int num_rows{};
  ceres::Manifold object{};
  object.RightMultiplyByPlusJacobian(nullptr, num_rows, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0920, TC2_CallsTarget) {
  const int num_rows{};
  ceres::Manifold object{};
  object.RightMultiplyByPlusJacobian(nullptr, num_rows, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0920, TC3_CallsTarget) {
  const int num_rows{};
  ceres::Manifold object{};
  object.RightMultiplyByPlusJacobian(nullptr, num_rows, nullptr, nullptr);
}
