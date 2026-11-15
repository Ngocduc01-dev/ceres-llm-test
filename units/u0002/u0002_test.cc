// FILE: u0002_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_first_order_function.h"

namespace {

// Functor bậc hai với 4 tham số: f(x) = sum(x_i^2)
struct QuadraticCostFunctor {
  template <typename T>
  bool operator()(const T* const x, T* cost) const {
    cost[0] = T(0.0);
    for (int i = 0; i < 4; ++i) {
      cost[0] += x[i] * x[i];
    }
    return true;
  }
};

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AutoDiffFirstOrderFunctionNumParametersTest, P1_ReturnsNumParameters) {
  // Constructor nhận con trỏ functor và sở hữu nó.
  ceres::AutoDiffFirstOrderFunction<QuadraticCostFunctor, 4> function(
      new QuadraticCostFunctor);
  function.NumParameters();  // Không kiểm tra kết quả trả về
}

}  // namespace
