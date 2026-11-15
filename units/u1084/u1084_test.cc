// FILE: u1084_test.cc
#include "gtest/gtest.h"
#include "ceres/stringprintf.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1084, TC1_CallsTarget) {
  ceres::internal::StringAppendF(nullptr, nullptr);
}
