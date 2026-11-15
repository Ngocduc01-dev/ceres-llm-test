// FILE: u0323_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0323, PathP1) {
  ceres::internal::LevenbergMarquardtStrategy target;
  target.Radius();
}
