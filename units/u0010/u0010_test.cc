// FILE: u0010_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

namespace {

// Functor đơn giản có phương thức Plus, dùng để khởi tạo PlusWrapper.
struct EuclideanFunctor {
  template <typename T>
  bool Plus(const T* x, const T* delta, T* x_plus_delta) const {
    for (int i = 0; i < 3; ++i) {
      x_plus_delta[i] = x[i] + delta[i];
    }
    return true;
  }
};

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(PlusWrapperOperatorTest, TC1_P1_GoiPlusMotLan) {
  EuclideanFunctor functor;
  ceres::internal::PlusWrapper<EuclideanFunctor> wrapper(functor);

  const double x[3] = {1.5, -2.0, 0.5};
  const double delta[3] = {0.25, 3.0, -1.0};
  double x_plus_delta[3] = {0.0, 0.0, 0.0};

  // Không kiểm tra kết quả trả về.
  wrapper(x, delta, x_plus_delta);
}

}  // namespace
