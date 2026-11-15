// FILE: u0437_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_cost_function.h"
#include "ceres/sized_cost_function.h"

namespace {

struct BinaryScalarCost {
  template <typename T>
  bool operator()(const T* x, const T* y, T* residual) const {
    residual[0] = x[0] * y[0] + x[1] * y[1];
    return true;
  }
};

// P1: node 1: đúng (jacobians == nullptr) -> node 2 -> END
TEST(AutoDiffCostFunctionEvaluateTest, NullJacobians) {
  BinaryScalarCost functor;
  ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2> cost_function(
      &functor, ceres::DO_NOT_TAKE_OWNERSHIP);

  double x[2] = {1.3, -0.7};
  double y[2] = {2.1, 0.4};
  const double* parameters[2] = {x, y};
  double residuals[1] = {0.0};

  cost_function.Evaluate(parameters, residuals, nullptr);
}

// P2: node 1: sai (jacobians != nullptr) -> node 3 -> END
TEST(AutoDiffCostFunctionEvaluateTest, NonNullJacobians) {
  BinaryScalarCost functor;
  ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2> cost_function(
      &functor, ceres::DO_NOT_TAKE_OWNERSHIP);

  double x[2] = {1.3, -0.7};
  double y[2] = {2.1, 0.4};
  const double* parameters[2] = {x, y};
  double residuals[1] = {0.0};
  double j0[2] = {0.0, 0.0};
  double j1[2] = {0.0, 0.0};
  double* jacobians[2] = {j0, j1};

  cost_function.Evaluate(parameters, residuals, jacobians);
}

}  // namespace
