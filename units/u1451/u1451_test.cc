// FILE: u1451_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1451, TC1_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.InternalSetManifold(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1451, TC2_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.InternalSetManifold(nullptr, nullptr, nullptr);
}
