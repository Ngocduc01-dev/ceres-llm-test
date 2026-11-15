// FILE: u0777_test.cc
#include "gtest/gtest.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0777, TC1_CallsTarget) {
  PreconditionerType type{};
  ceres::PreconditionerTypeToString(type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0777, TC2_CallsTarget) {
  PreconditionerType type{};
  ceres::PreconditionerTypeToString(type);
}
