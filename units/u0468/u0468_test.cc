// FILE: u0468_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0468, PathP1) {
  const int arg_0 = 1;
  const bool arg_1 = true;
  ceres::internal::BFGS target(arg_0, arg_1);
  target.BFGS(1, true);
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0468, PathP2) {
  const int arg_0 = 1;
  const bool arg_1 = true;
  ceres::internal::BFGS target(arg_0, arg_1);
  target.BFGS(1, true);
}
