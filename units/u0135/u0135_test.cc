// FILE: u0135_test.cc
#include <random>

#include "ceres/jet.h"
#include "gtest/gtest.h"

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetIsNormalTest, SinglePathNoBranch) {
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(1.0, 5.0);

  Jet<double, 1> f;
  f.a = dist(gen);
  f.v[0] = dist(gen);

  bool result = isnormal(f);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace
}  // namespace ceres
