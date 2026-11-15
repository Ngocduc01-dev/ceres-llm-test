// FILE: u1350_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END
TEST(u1350_Test, TC1_CallsTarget) {
  ceres::internal::LineSearch target{};
  target.Search(nullptr, nullptr, nullptr, nullptr);
}
