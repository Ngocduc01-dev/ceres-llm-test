// FILE: u1083_test.cc
#include "gtest/gtest.h"
#include "ceres/stringprintf.h"

// P1: START -> 1 -> END
TEST(SStringPrintfTest, TC1_CallsTarget) {
  char a1[8] = {};
  ceres::internal::SStringPrintf(nullptr, a1);
}

