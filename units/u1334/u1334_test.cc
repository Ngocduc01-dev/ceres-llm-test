// FILE: u1334_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1334, TC1_CallsTarget) {
  int index{};
  ceres::Problem object{};
  object.GetParameterUpperBound(nullptr, index);
}
