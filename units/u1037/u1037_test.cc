// FILE: u1037_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1037, TC1_CallsTarget) {
  int index{};
  double lower_bound{};
  ceres::internal::ProblemImpl object{};
  object.SetParameterLowerBound(nullptr, index, lower_bound);
}
