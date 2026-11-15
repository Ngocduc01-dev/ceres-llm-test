// FILE: u0647_test.cc
#include "gtest/gtest.h"
#include "ceres/tiny_solver_autodiff_function.h"

// Path P1 calls TinySolverAutoDiffFunction(const CostFunctor & cost_functor).
TEST(Unitu0647, CallsTarget) {
  object.TinySolverAutoDiffFunction({});
}
