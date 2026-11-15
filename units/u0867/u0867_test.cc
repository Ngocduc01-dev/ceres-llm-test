// FILE: u0867_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0867, TC1_CallsTarget) {
  ceres::internal::LineSearch object{};
  object.~LineSearch();
}
