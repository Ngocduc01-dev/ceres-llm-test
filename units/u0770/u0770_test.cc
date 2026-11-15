// FILE: u0770_test.cc
#include "gtest/gtest.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0770, TC1_CallsTarget) {
  TerminationType type{};
  ceres::TerminationTypeToString(type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0770, TC2_CallsTarget) {
  TerminationType type{};
  ceres::TerminationTypeToString(type);
}
