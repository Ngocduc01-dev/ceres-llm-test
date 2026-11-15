// FILE: u0115_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// TC1 - Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetTanhTest, SingleStraightLinePath) {
  Jet<double, 2> f;
  f.a = 0.37;
  f.v[0] = -1.21;
  f.v[1] = 0.84;

  Jet<double, 2> r = tanh(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace ceres
