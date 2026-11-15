// FILE: u0518_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> 2 -> 3 -> 4 -> END.
TEST(Unit_u0518, PathP1) {
  ceres::Jet<double, 2> f(2.0);
  ceres::Jet<double, 2> g(1.0);
  ceres::fdim(f, g);
}
