// FILE: u1343_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1343_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
}
