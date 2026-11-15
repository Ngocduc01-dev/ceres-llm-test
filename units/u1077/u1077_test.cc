// FILE: u1077_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1077, TC1_CallsTarget) {
  std::string name{};
  ceres::internal::ScopedExecutionTimer object{};
  (void)object;
}
