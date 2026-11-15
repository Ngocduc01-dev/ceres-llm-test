// FILE: u0616_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_first_order_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0616, CallsTarget) {
  double functor_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.AutoDiffFirstOrderFunction(functor_data);
}
