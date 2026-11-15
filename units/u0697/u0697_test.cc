// FILE: u0697_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_first_order_function.h"
#include "ceres/numeric_diff_options.h"

struct LocalDynamicFirstOrderFunctor {};
// Path P1: START -> 1 -> 2 -> END.
TEST(Unit_u0697, PathP1) {
  ceres::NumericDiffFirstOrderFunction<LocalDynamicFirstOrderFunctor, ceres::CENTRAL> target(nullptr, 1);
}
