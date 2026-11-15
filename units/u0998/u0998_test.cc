// FILE: u0998_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0998, TC1_CallsTarget) {
  ceres::internal::ScopedExecutionTimer object{};
  object.~ScopedExecutionTimer();
}
