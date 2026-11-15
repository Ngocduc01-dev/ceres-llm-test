// FILE: u0108_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetAcosTest, P1_SingleStraightPath) {
  Jet<double, 2> f;
  f.a = 0.37;
  f.v[0] = 1.5;
  f.v[1] = -2.0;

  Jet<double, 2> r = acos(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
