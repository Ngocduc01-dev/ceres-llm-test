// FILE: u0104_test.cc
#include <random>

#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetExpTest, SinglePath) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-2.0, 2.0);

  ceres::Jet<double, 2> f;
  f.a = dist(gen);
  f.v[0] = dist(gen);
  f.v[1] = dist(gen);

  ceres::Jet<double, 2> r = ceres::exp(f);
  (void)r;  // Không kiểm tra kết quả trả về
}
