// FILE: u0190_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_first_order_function.h"

namespace ceres {
namespace {

// Functor bậc nhất đơn giản với 4 tham số.
struct QuadraticCostFunctor {
  bool operator()(const double* parameters, double* cost) const {
    double sum = 0.0;
    for (int i = 0; i < 4; ++i) {
      sum += parameters[i] * parameters[i];
    }
    *cost = sum;
    return true;
  }
};

// Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(NumericDiffFirstOrderFunctionNumParametersTest, TC1_ReturnNumParameters) {
  NumericDiffOptions options;
  NumericDiffFirstOrderFunction<QuadraticCostFunctor, CENTRAL, 4> function(
      new QuadraticCostFunctor(), TAKE_OWNERSHIP, options);
  function.NumParameters();
}

}  // namespace
}  // namespace ceres
