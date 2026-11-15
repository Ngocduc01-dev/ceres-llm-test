// FILE: u0757_test.cc
#include "gtest/gtest.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0757, TC1_CallsTarget) {
  NumericDiffMethodType type{};
  ceres::NumericDiffMethodTypeToString(type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0757, TC2_CallsTarget) {
  NumericDiffMethodType type{};
  ceres::NumericDiffMethodTypeToString(type);
}
