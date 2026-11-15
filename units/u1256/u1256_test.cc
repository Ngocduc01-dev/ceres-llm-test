// FILE: u1256_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1256, TC1_CallsTarget) {
  ceres::Solver::Summary object{};
  object.BriefReport();
}
