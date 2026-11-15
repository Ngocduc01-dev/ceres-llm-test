// FILE: u0024_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

namespace ceres {
namespace internal {

// P1: START -> END (hàm rỗng, không có điểm rẽ nhánh)
TEST(Make1stOrderPerturbationsEmptyApply, TC1_StartToEnd) {
  using JetT = Jet<double, 4>;
  Make1stOrderPerturbations<std::integer_sequence<int>, 0, 0> obj;

  double p = 1.5;
  double const* parameters[1] = {&p};
  JetT x[2];

  obj.Apply<double, JetT>(parameters, x);
}

}  // namespace internal
}  // namespace ceres
