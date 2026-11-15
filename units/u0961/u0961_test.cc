// FILE: u0961_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END
TEST(optionsTest, TC1_CallsTarget) {
  LineSearch object{};
  object.options();
}

