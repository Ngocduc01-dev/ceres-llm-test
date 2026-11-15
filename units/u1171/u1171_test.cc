// FILE: u1171_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1171, TC1_CallsTarget) {
  const LineSearchType line_search_type{};
  LineSearch::Options options{};
  ceres::internal::LineSearch object{};
  object.Create(line_search_type, options, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1171, TC2_CallsTarget) {
  const LineSearchType line_search_type{};
  LineSearch::Options options{};
  ceres::internal::LineSearch object{};
  object.Create(line_search_type, options, nullptr);
}
