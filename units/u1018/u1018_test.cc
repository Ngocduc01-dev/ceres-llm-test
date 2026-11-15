// FILE: u1018_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1018, TC1_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.NumResidualBlocks();
}
