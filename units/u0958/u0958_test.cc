// FILE: u0958_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ComputeCauchyPointTest, TC1_CallsTarget) {
  DoglegStrategy object{};
  object.ComputeCauchyPoint(nullptr);
}

