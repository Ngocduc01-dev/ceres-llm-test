// FILE: u0547_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> 2 -> 3 -> END.
TEST(Unit_u0547, PathP1) {
  ceres::Jet<double, 2> x(1.0), y(2.0);
  ceres::fmin(x, y);
}
