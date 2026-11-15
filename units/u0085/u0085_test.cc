// FILE: u0085_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMultiplyJetScalar, P1_SequentialPath) {
  using JetType = ceres::Jet<double, 4>;

  JetType f;
  f.a = 3.0;
  f.v[0] = 1.0;
  f.v[1] = -2.0;
  f.v[2] = 4.0;
  f.v[3] = 5.0;

  const double s = 2.0;

  JetType result = ceres::operator*(f, s);
  (void)result;  // Không kiểm tra kết quả trả về
}
