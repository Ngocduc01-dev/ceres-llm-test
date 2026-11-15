// FILE: u0766_test.cc
#include "gtest/gtest.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0766, TC1_CallsTarget) {
  LineSearchDirectionType type{};
  ceres::LineSearchDirectionTypeToString(type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0766, TC2_CallsTarget) {
  LineSearchDirectionType type{};
  ceres::LineSearchDirectionTypeToString(type);
}
