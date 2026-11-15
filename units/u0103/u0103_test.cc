// FILE: u0103_test.cc
#include <random>

#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(Log1pJetTest, P1_StraightLine) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist_a(-0.9, 5.0);
  std::uniform_real_distribution<double> dist_v(-5.0, 5.0);

  ceres::Jet<double, 2> f;
  f.a = dist_a(gen);
  f.v[0] = dist_v(gen);
  f.v[1] = dist_v(gen);

  ceres::Jet<double, 2> result = ceres::log1p(f);
  (void)result;  // Không kiểm tra kết quả trả về.
}
