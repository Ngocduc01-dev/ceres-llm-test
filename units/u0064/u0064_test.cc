// FILE: u0064_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/variadic_evaluate.h"

namespace ceres {
namespace internal {

namespace {

// Functor kiểu dynamic: nhận mảng con trỏ input và con trỏ output.
struct DynamicCost {
  bool operator()(double const* const* input, double* output) const {
    output[0] = input[0][0] + input[1][0];
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END
TEST(VariadicEvaluateImplDynamicTest, TC1_ReturnFunctorCall) {
  const double a[1] = {1.5};
  const double b[1] = {2.5};
  double const* const input[2] = {a, b};
  double output[1] = {0.0};
  DynamicCost functor;

  VariadicEvaluateImpl(functor,
                       input,
                       output,
                       std::true_type(),
                       std::integer_sequence<int>());
}

}  // namespace internal
}  // namespace ceres
