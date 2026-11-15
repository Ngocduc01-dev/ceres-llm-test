// FILE: u0789_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

// P1: START -> 1 -> END
TEST(EvaluateSubspaceModelTest, TC1_CallsTarget) {
  DoglegStrategy object{};
  Vector2d & x a0{};
  object.EvaluateSubspaceModel(a0);
}

