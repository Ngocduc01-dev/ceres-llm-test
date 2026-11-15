// FILE: u1056_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1056, TC1_CallsTarget) {
  const int num_rows{};
  ceres::SubsetManifold object{};
  object.RightMultiplyByPlusJacobian(nullptr, num_rows, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1056, TC2_CallsTarget) {
  const int num_rows{};
  ceres::SubsetManifold object{};
  object.RightMultiplyByPlusJacobian(nullptr, num_rows, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1056, TC3_CallsTarget) {
  const int num_rows{};
  ceres::SubsetManifold object{};
  object.RightMultiplyByPlusJacobian(nullptr, num_rows, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1056, TC4_CallsTarget) {
  const int num_rows{};
  ceres::SubsetManifold object{};
  object.RightMultiplyByPlusJacobian(nullptr, num_rows, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1056, TC5_CallsTarget) {
  const int num_rows{};
  ceres::SubsetManifold object{};
  object.RightMultiplyByPlusJacobian(nullptr, num_rows, nullptr, nullptr);
}
