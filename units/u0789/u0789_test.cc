// FILE: u0789_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0789, TC1_CallsTarget) {
  Vector2d x{};
  ceres::internal::DoglegStrategy object{};
  object.EvaluateSubspaceModel(x);
}
