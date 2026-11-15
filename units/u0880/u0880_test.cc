// FILE: u0880_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(operator=Test, TC1_CallsTarget) {
  Problem object{};
  Problem && a0{};
  object.operator=(a0);
}

