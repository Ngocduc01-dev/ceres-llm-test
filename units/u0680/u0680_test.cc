// FILE: u0680_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0680, PathP1) {
  ceres::internal::LineSearchFunction target(nullptr);
  ceres::internal::Vector position(1);
  ceres::internal::Vector direction(1);
  target.Init(position, direction);
}
