// FILE: u0011_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

namespace ceres {
namespace internal {

namespace {

// Functor tối thiểu có method template Minus để MinusWrapper gọi tới.
struct EuclideanFunctor {
  template <typename T>
  bool Minus(const T* y, const T* x, T* y_minus_x) const {
    for (int i = 0; i < 3; ++i) {
      y_minus_x[i] = y[i] - x[i];
    }
    return true;
  }
};

}  // namespace

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(MinusWrapperOperatorTest, P1_CallMinusWithJet) {
  using JetT = Jet<double, 6>;

  EuclideanFunctor functor;
  MinusWrapper<EuclideanFunctor> wrapper(functor);

  const JetT y[3] = {JetT(1.5), JetT(-2.0), JetT(3.25)};
  const JetT x[3] = {JetT(0.5), JetT(4.0), JetT(-1.25)};
  JetT y_minus_x[3] = {JetT(0.0), JetT(0.0), JetT(0.0)};

  // Không kiểm tra kết quả trả về, chỉ gọi unit một lần.
  wrapper(y, x, y_minus_x);
}

}  // namespace internal
}  // namespace ceres
