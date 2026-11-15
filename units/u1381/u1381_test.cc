// FILE: u1381_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(u1381_Test, TC1_CallsTarget) {
  ceres::internal::ProblemImpl target{};
  target.NumResiduals();
}
