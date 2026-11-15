// FILE: u0548_test.cc
#include "gtest/gtest.h"
#include "ceres/tiny_solver_autodiff_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0548, CallsTarget) {
  double jacobian_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.operator(jacobian_data);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0548, CallsTargetAlternate) {
  double jacobian_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.operator(jacobian_data);
}
