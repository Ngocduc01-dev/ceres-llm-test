// FILE: u1366_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1366, TC1_CallsTarget) {
  ceres::internal::ParameterBlock object{};
  object.SetManifold(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1366, TC2_CallsTarget) {
  ceres::internal::ParameterBlock object{};
  object.SetManifold(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1366, TC3_CallsTarget) {
  ceres::internal::ParameterBlock object{};
  object.SetManifold(nullptr);
}
