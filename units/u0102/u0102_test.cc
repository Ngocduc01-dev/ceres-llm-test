// FILE: u0102_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(Log10JetTest, P1_SequentialPath) {
  ceres::Jet<double, 2> f;
  f.a = 3.7;
  f.v[0] = 1.3;
  f.v[1] = -2.4;

  ceres::Jet<double, 2> r = ceres::log10(f);
  (void)r;
}
