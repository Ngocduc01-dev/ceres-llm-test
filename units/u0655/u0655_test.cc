// FILE: u0655_test.cc
#include "gtest/gtest.h"
#include "ceres/conjugate_gradients_solver.h"
#include "ceres/linear_operator.h"

// Path P1 calls LinearOperatorAdapter(LinearOperator & linear_operator).
TEST(Unitu0655, CallsTarget) {
  object.LinearOperatorAdapter({});
}
