// FILE: u0876_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0876, TC1_CallsTarget) {
  ceres::internal::ParameterBlock object{};
  object.manifold();
}
