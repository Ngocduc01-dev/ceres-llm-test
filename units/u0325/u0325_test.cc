// FILE: u0325_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0325, PathP1) {
  ceres::internal::LineSearchFunction target;
  target.position();
}
