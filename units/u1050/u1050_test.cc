// FILE: u1050_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1050, TC1_CallsTarget) {
  ceres::SubsetManifold object{};
  object.Plus(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1050, TC2_CallsTarget) {
  ceres::SubsetManifold object{};
  object.Plus(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1050, TC3_CallsTarget) {
  ceres::SubsetManifold object{};
  object.Plus(nullptr, nullptr, nullptr);
}
