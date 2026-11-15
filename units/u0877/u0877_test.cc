// FILE: u0877_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/parameter_block.h"

// P1: START -> 1 -> END
TEST(mutable_manifoldTest, TC1_CallsTarget) {
  ParameterBlock object{};
  object.mutable_manifold();
}

