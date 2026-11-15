// FILE: u0797_test.cc
#include "gtest/gtest.h"
#include "ceres/types.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0797, TC1_CallsTarget) {
  ceres::UpperCase(nullptr);
}
