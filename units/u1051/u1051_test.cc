// FILE: u1051_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1051, TC1_CallsTarget) {
  ceres::SubsetManifold object{};
  object.MinusJacobian(nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1051, TC2_CallsTarget) {
  ceres::SubsetManifold object{};
  object.MinusJacobian(nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1051, TC3_CallsTarget) {
  ceres::SubsetManifold object{};
  object.MinusJacobian(nullptr, nullptr);
}
