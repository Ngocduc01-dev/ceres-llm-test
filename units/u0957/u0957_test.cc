// FILE: u0957_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(ComputeGradientTest, TC1_CallsTarget) {
  DoglegStrategy object{};
  double a1[5] = {};
  object.ComputeGradient(nullptr, a1);
}

