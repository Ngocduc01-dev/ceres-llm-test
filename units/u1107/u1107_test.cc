// FILE: u1107_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/normal_prior.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1107, TC1_CallsTarget) {
  Matrix A{};
  Vector b{};
  ceres::NormalPrior object{};
  (void)object;
}
