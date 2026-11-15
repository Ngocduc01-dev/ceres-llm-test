// FILE: u0445_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/array_selector.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0445, PathP1) {
  int arg_0 = 1;
  ceres::ArraySelector<int, -1, 20> target(arg_0);
  target.ArraySelector<type-parameter-0-0, num_elements, max_num_elements_on_stack, false, true>(1);
}
