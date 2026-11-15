// FILE: u0248_test.cc
#include "gtest/gtest.h"
#include "ceres/callbacks.h"

// Path P1: START -> 1 -> END
TEST(GradientProblemSolverStateUpdatingCallbackTest, ConstructorP1) {
  double internal_parameters[3] = {0.5, 1.5, 2.5};
  double user_parameters[3] = {0.0, 0.0, 0.0};
  ceres::internal::GradientProblemSolverStateUpdatingCallback callback(
      3, internal_parameters, user_parameters);
}
