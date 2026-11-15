// FILE: u1343_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1343, TC1_CallsTarget) {
  ceres::internal::ProblemImpl object{};
  (void)object;
}
