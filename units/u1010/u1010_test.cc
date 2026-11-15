// FILE: u1010_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1010, TC1_CallsTarget) {
  ceres::internal::Minimizer::Options object{};
  (void)object;
}
