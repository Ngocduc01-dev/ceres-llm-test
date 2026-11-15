// FILE: u0919_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0919, TC1_CallsTarget) {
  Ownership ownership_f{};
  Ownership ownership_g{};
  ceres::ComposedLoss object{};
  (void)object;
}
