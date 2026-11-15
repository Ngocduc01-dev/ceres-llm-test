// FILE: u0063_test.cc
#include <random>
#include <type_traits>
#include <utility>

#include "ceres/internal/variadic_evaluate.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

namespace {

struct BinaryScalarCost {
  bool operator()(const double* x, const double* y, double* out) const {
    out[0] = x[0] + y[0];
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END
TEST(VariadicEvaluateImplTest, TwoBlocksNonDynamic) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-5.0, 5.0);

  double x[1] = {dist(gen)};
  double y[1] = {dist(gen)};
  const double* input[2] = {x, y};
  double output[1] = {0.0};

  BinaryScalarCost functor;
  bool result = VariadicEvaluateImpl(functor,
                                     input,
                                     output,
                                     std::false_type{},
                                     std::integer_sequence<int, 0, 1>{});
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace internal
}  // namespace ceres
