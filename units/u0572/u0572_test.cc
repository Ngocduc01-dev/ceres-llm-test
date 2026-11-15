// FILE: u0572_test.cc
#include "gtest/gtest.h"
#include "ceres/tiny_solver_autodiff_function.h"

// Path P1 calls Initialize(const CostFunctor& function).
TEST(Unitu0572, CallsTarget) {
  object.Initialize({});
}
