// FILE: u0315_test.cc
#include "gtest/gtest.h"
#include "ceres/inner_product_computer.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0315, PathP1) {
  const int arg_0 = 1;
  const int arg_1 = 1;
  const int arg_2 = 1;
  ceres::internal::InnerProductComputer::ProductTerm target(arg_0, arg_1, arg_2);
  target.ProductTerm(1, 1, 1);
}
