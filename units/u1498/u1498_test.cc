// FILE: u1498_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1498, TC1_CallsTarget) {
  int size{};
  ceres::internal::ProblemImpl object{};
  object.AddParameterBlock(nullptr, size);
}
