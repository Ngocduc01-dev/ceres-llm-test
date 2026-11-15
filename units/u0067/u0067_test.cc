// FILE: u0067_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/variadic_evaluate.h"

namespace ceres {
namespace internal {

namespace {

// Functor bậc nhất đơn giản: cost = x^2 (nhận một khối tham số).
struct QuadraticCostFunctor {
  bool operator()(const double* x, double* cost) const {
    cost[0] = x[0] * x[0];
    return true;
  }
};

}  // namespace

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(FirstOrderFunctorAdapterTest, TC1_CallFunctorOnce) {
  QuadraticCostFunctor functor;
  FirstOrderFunctorAdapter<QuadraticCostFunctor> adapter(functor);

  double x[1] = {3.0};
  const double* parameters[1] = {x};
  double cost = 0.0;

  (void)adapter(parameters, &cost);
}

}  // namespace internal
}  // namespace ceres
