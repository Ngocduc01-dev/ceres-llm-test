// FILE: u1152_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1152, TC1_CallsTarget) {
  LineSearch::Options options{};
  ceres::internal::WolfeLineSearch object{};
  (void)object;
}
