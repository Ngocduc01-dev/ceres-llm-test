// FILE: u0191_test.cc
#include <random>

#include "ceres/numeric_diff_first_order_function.h"
#include "gtest/gtest.h"

namespace ceres {
namespace {

struct QuadraticFunctor {
  explicit QuadraticFunctor(double s) : scale(s) {}
  bool operator()(const double* parameters, double* cost) const {
    cost[0] = scale * (parameters[0] * parameters[0] +
                       parameters[1] * parameters[1]);
    return true;
  }
  double scale;
};

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumericDiffFirstOrderFunctionTest, FunctorReturnsReference) {
  std::mt19937 gen(12345);
  std::uniform_int_distribution<int> dist(1, 5);
  QuadraticFunctor functor(static_cast<double>(dist(gen)));

  NumericDiffFirstOrderFunction<QuadraticFunctor, CENTRAL, 2> function(
      &functor, DO_NOT_TAKE_OWNERSHIP, NumericDiffOptions());

  const QuadraticFunctor& result = function.functor();
  (void)result;
}

}  // namespace
}  // namespace ceres
