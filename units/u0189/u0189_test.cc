// FILE: u0189_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_cost_function.h"

namespace {

struct SimpleFunctor {
  bool operator()(const double* x, double* residual) const {
    residual[0] = x[0];
    return true;
  }
};

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericDiffCostFunctionFunctorTest, P1_ReturnsFunctorReference) {
  ceres::NumericDiffOptions options;
  ceres::NumericDiffCostFunction<SimpleFunctor, ceres::CENTRAL, 1, 1>
      cost_function(new SimpleFunctor, ceres::TAKE_OWNERSHIP, 1, options);

  const SimpleFunctor& f = cost_function.functor();
  (void)f;
}

}  // namespace
