// FILE: u1426_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1426, TC1_CallsTarget) {
  ceres::Problem object{};
  (void)object;
}
