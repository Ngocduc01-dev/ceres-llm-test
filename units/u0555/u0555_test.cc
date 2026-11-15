// FILE: u0555_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0555, PathP1) {
  ceres::Jet<double, 2> base(2.0), exponent(2.0);
  ceres::pow<double, 2>(base, exponent);
}
