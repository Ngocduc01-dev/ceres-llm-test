// FILE: u0083_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMinusScalarJet, ScalarMinusJet) {
  using JetT = Jet<double, 4>;

  const double s = 3.5;
  JetT f;
  f.a = 1.25;
  f.v[0] = 0.5;
  f.v[1] = -1.5;
  f.v[2] = 2.0;
  f.v[3] = 4.0;

  // Gọi unit đúng một lần; không kiểm tra kết quả trả về.
  JetT r = operator-(s, f);
  (void)r;
}

}  // namespace
}  // namespace ceres
