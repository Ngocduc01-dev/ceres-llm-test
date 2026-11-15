// FILE: u1023_test.cc
#include "gtest/gtest.h"
#include "ceres/stringprintf.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1023, TC1_CallsTarget) {
  ceres::internal::StringPrintf(nullptr);
}
