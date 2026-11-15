// FILE: u0070_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetConstructorValueK, TC1_SequentialPath) {
  const double value = 3.5;
  const int k = 2;
  ceres::Jet<double, 4> j(value, k);
  (void)j;
}
