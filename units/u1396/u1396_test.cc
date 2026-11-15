// FILE: u1396_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"
#include "ceres/function_sample.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1396, TC1_CallsTarget) {
  std::ostream os{};
  FunctionSample sample{};
  ceres::internal::operator<<(os, sample);
}
