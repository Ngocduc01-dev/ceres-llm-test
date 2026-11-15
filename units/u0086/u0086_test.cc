// FILE: u0086_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetScalarTimesJetTest, P1_ScalarTimesJet) {
  const double s = 3.0;
  Jet<double, 4> f(2.0);
  f.v[0] = 1.0;
  f.v[1] = -2.0;
  f.v[2] = 0.5;
  f.v[3] = 4.0;

  // Gọi unit một lần; không kiểm tra kết quả trả về.
  Jet<double, 4> r = operator*(s, f);
  (void)r;
}

}  // namespace internal
}  // namespace ceres
