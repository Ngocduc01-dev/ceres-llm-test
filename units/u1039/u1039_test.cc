// FILE: u1039_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1039, TC1_CallsTarget) {
  int index{};
  ceres::internal::ProblemImpl object{};
  object.GetParameterLowerBound(nullptr, index);
}
