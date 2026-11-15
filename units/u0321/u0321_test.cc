// FILE: u0321_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0321, PathP1) {
  { ceres::internal::LevenbergMarquardtStrategy target; }
}
