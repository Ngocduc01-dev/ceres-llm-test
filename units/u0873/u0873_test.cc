// FILE: u0873_test.cc
#include "gtest/gtest.h"
#include "ceres/minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0873, TC1_CallsTarget) {
  ceres::internal::Minimizer object{};
  object.~Minimizer();
}
