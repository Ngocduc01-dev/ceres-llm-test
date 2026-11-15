// FILE: u1244_test.cc
#include "gtest/gtest.h"
#include "ceres/function_sample.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1244, TC1_CallsTarget) {
  ceres::internal::FunctionSample object{};
  object.ToDebugString();
}
