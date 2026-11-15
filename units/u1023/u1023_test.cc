// FILE: u1023_test.cc
#include "gtest/gtest.h"
#include "ceres/stringprintf.h"

// P1: START -> 1 -> END
TEST(StringPrintfTest, TC1_CallsTarget) {
  char a0[8] = {};
  ceres::internal::StringPrintf(a0);
}

