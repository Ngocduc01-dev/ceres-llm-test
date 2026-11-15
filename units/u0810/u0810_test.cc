// FILE: u0810_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"
#include "ceres/linear_least_squares_problems.cc"

// P1: START -> 1 -> END
TEST(WriteArrayToFileOrDieTest, TC1_CallsTarget) {
  std::string & filename a0;
  double a1[5] = {};
  int a2 = 0;
  WriteArrayToFileOrDie(a0, a1, a2);
}

// P2: START -> 1 -> END
TEST(WriteArrayToFileOrDieTest, TC2_CallsTarget) {
  std::string & filename a0;
  double a1[5] = {};
  int a2 = 0;
  WriteArrayToFileOrDie(a0, a1, a2);
}

