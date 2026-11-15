// FILE: u0885_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0885, TC1_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  object.context();
}
