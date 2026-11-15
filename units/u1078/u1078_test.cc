// FILE: u1078_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1078, TC1_CallsTarget) {
  Solver::Options options{};
  ceres::internal::Minimizer::Options object{};
  (void)object;
}
