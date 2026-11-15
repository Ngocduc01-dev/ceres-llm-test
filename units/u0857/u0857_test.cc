// FILE: u0857_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0857, TC1_CallsTarget) {
  ceres::internal::Evaluator object{};
  object.~Evaluator();
}
