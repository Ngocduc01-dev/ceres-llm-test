// FILE: u0719_test.cc
#include "gtest/gtest.h"
#include "ceres/tiny_solver.h"

struct LocalTinyFunction {
  using Scalar = double;
  static constexpr int NUM_RESIDUALS = 1;
  static constexpr int NUM_PARAMETERS = 1;
  bool operator()(const double*, double* residual, double* jacobian) const {
    residual[0] = 1.0;
    jacobian[0] = 1.0;
    return true;
  }
};
// Path P1: START -> 1 -> 3 -> 4 -> 5 -> 6 -> END.
TEST(Unit_u0719, PathP1) {
  ceres::TinySolver<LocalTinyFunction> target;
  LocalTinyFunction function;
  ceres::TinySolver<LocalTinyFunction>::Parameters x;
  x[0] = 0.0;
  target.summary.iterations = 0;
  target.Update(function, x);
}
