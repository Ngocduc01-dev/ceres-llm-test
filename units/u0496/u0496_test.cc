// FILE: u0496_test.cc
#include "gtest/gtest.h"
#include <utility>
#include "ceres/internal/numeric_diff.h"

namespace ceres {
namespace internal {
namespace {
struct CostFunctor {
  bool operator()(const double* parameters, double* residuals) const {
    residuals[0] = parameters[0] * parameters[0];
    return true;
  }
};
}  // namespace

TEST(Unit_u0496, EvaluatesParameterBlockJacobian) {
  CostFunctor functor;
  NumericDiffOptions options;
  double value = 2.0;
  double* parameters[] = {&value};
  double residuals[1] = {4.0};
  double jacobian[1] = {};
  double* jacobians[] = {jacobian};

  const bool success =
      EvaluateJacobianForParameterBlocks<ParameterDims<false, 1>,
                                         std::integer_sequence<int, 1>>::
          Apply<CENTRAL, 1>(&functor, residuals, options, 1, parameters,
                            jacobians);

  EXPECT_TRUE(success);
  EXPECT_NEAR(jacobian[0], 4.0, 1e-6);
}

}  // namespace internal
}  // namespace ceres
