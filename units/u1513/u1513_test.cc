// FILE: u1513_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1513, TC1_CallsTarget) {
  int size{};
  ceres::internal::ProblemImpl object{};
  object.AddParameterBlock(nullptr, size, nullptr);
}
