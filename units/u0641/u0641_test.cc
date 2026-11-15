// FILE: u0641_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_first_order_function.h"
#include "ceres/numeric_diff_options.h"

struct LocalFirstOrderFunctor {};
// Path P1: START -> 1 -> END.
TEST(Unit_u0641, PathP1) {
  ceres::NumericDiffFirstOrderFunction<LocalFirstOrderFunctor, ceres::CENTRAL, 4> target(nullptr);
}
