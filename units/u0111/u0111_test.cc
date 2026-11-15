// FILE: u0111_test.cc
#include <random>

#include "ceres/jet.h"
#include "gtest/gtest.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetTanTest, SinglePathNoBranch) {
  std::mt19937 gen(12345);
  std::uniform_real_distribution<double> a_dist(-1.5, 1.5);
  std::uniform_real_distribution<double> v_dist(-5.0, 5.0);

  Jet<double, 2> f;
  f.a = a_dist(gen);
  f.v[0] = v_dist(gen);
  f.v[1] = v_dist(gen);

  Jet<double, 2> result = tan(f);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
