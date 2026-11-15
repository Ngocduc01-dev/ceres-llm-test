// FILE: u0750_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"
#include <sstream>

// Path P1: START -> 1 -> END.
TEST(Unit_u0750, PathP1) {
  std::ostringstream stream;
  ceres::internal::operator<<(stream, ceres::internal::OrderingType::NATURAL);
}
