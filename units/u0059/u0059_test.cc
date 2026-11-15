// FILE: u0059_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/numeric_diff.h"
#include "ceres/numeric_diff_options.h"

namespace ceres {
namespace internal {

namespace {

struct DummyCostFunctor {
  bool operator()(const double* const x, double* residual) const {
    residual[0] = x[0];
    return true;
  }
};

}  // namespace

// P1: START -> return true -> END (không có điểm rẽ nhánh)
TEST(EvaluateJacobianForParameterBlocksTest, TerminalApplyReturnsTrue) {
  EvaluateJacobianForParameterBlocks<ParameterDims<false, 4>,
                                     std::integer_sequence<int>,
                                     1>
      obj;

  DummyCostFunctor functor;
  double parameters[1] = {1.0};
  NumericDiffOptions options;
  int num_residuals = 1;
  double** residuals_at_eval_point = nullptr;
  double** jacobians = nullptr;

  obj.Apply<CENTRAL, 1>(&functor,
                        parameters,
                        options,
                        num_residuals,
                        residuals_at_eval_point,
                        jacobians);
}

}  // namespace internal
}  // namespace ceres
