// FILE: u1083_test.cc
#include "gtest/gtest.h"
#include "ceres/stringprintf.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1083, TC1_CallsTarget) {
  ceres::internal::SStringPrintf(nullptr, nullptr);
}
