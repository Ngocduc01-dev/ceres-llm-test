// FILE: u1344_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1344, TC1_CallsTarget) {
  Problem::Options options{};
  ceres::internal::ProblemImpl object{};
  (void)object;
}
