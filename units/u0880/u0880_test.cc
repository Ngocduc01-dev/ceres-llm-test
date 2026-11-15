// FILE: u0880_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0880, TC1_CallsTarget) {
  Problem arg0{};
  ceres::Problem object{};
  object(arg0);
}
