// FILE: u0577_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

// Path P1 calls MakePolynomialForBoundaryConstrainedProblem() const.
TEST(Unitu0577, CallsTarget) {
  object.MakePolynomialForBoundaryConstrainedProblem();
}
