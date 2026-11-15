// FILE: u1344_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1344_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
}
