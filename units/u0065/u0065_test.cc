// FILE: u0065_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/variadic_evaluate.h"

namespace ceres {
namespace internal {

namespace {

// Functor 2 khối tham số (mỗi khối 2 phần tử), 1 residual.
struct BinaryScalarCost {
  bool operator()(const double* x, const double* y, double* out) const {
    out[0] = x[0] * y[0] + x[1] * y[1];
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(VariadicEvaluateImplTest, TC1_StaticTwoBlocks) {
  BinaryScalarCost functor;
  const double x[2] = {1.5, -2.0};
  const double y[2] = {3.0, 0.5};
  const double* const input[2] = {x, y};
  double output[1] = {0.0};

  // Không kiểm tra kết quả trả về.
  VariadicEvaluateImpl<ParameterDims<false, 2, 2>>(
      functor, input, output, nullptr);
}

}  // namespace internal
}  // namespace ceres
