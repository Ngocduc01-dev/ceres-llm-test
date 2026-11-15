// FILE: u0066_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/variadic_evaluate.h"

namespace ceres {
namespace internal {

// Functor hai khối tham số, mỗi khối có kích thước 2 (khớp ParameterDims<false, 2, 2>).
struct BinaryScalarCost {
  template <typename T>
  bool operator()(const T* x, const T* y, T* residual) const {
    residual[0] = x[0] - y[0];
    residual[1] = x[1] - y[1];
    return true;
  }
};

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(VariadicEvaluateTest, P1_SinglePath) {
  const double x[2] = {1.5, -0.7};
  const double y[2] = {0.3, 2.1};
  const double* const input[2] = {x, y};
  double output[2] = {0.0, 0.0};
  BinaryScalarCost functor;

  VariadicEvaluate<ParameterDims<false, 2, 2>>(functor, input, output);
}

}  // namespace internal
}  // namespace ceres
