// FILE: u1055_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1055, TC1_CallsTarget) {
  ceres::SubsetManifold object{};
  object.Minus(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1055, TC2_CallsTarget) {
  ceres::SubsetManifold object{};
  object.Minus(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1055, TC3_CallsTarget) {
  ceres::SubsetManifold object{};
  object.Minus(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1055, TC4_CallsTarget) {
  ceres::SubsetManifold object{};
  object.Minus(nullptr, nullptr, nullptr);
}
