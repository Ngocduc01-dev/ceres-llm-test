// FILE: u1244_test.cc
#include "gtest/gtest.h"
#include "ceres/function_sample.h"

// P1: START -> 1 -> END
TEST(ToDebugStringTest, TC1_CallsTarget) {
  FunctionSample object{};
  object.ToDebugString();
}

