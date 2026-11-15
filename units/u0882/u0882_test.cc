// FILE: u0882_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0882, TC1_CallsTarget) {
  ceres::Problem object{};
  object.mutable_impl();
}
