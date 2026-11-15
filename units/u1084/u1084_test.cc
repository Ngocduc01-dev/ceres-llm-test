// FILE: u1084_test.cc
#include "gtest/gtest.h"
#include "ceres/stringprintf.h"

// P1: START -> 1 -> END
TEST(StringAppendFTest, TC1_CallsTarget) {
  char a1[8] = {};
  ceres::internal::StringAppendF(nullptr, a1);
}

