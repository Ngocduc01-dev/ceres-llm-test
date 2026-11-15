// FILE: u1041_test.cc
#include "gtest/gtest.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1041, TC1_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.ParameterBlockSize(nullptr);
}
