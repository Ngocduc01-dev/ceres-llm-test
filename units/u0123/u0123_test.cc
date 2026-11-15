// FILE: u0123_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetFmaTest, TC1_SingleStraightPath) {
  using JetT = Jet<double, 2>;

  JetT x(1.5);
  x.v[0] = 0.5;
  x.v[1] = -2.0;

  JetT y(-3.0);
  y.v[0] = 1.0;
  y.v[1] = 4.0;

  JetT z(2.5);
  z.v[0] = -1.5;
  z.v[1] = 3.0;

  JetT r = fma(x, y, z);
  (void)r;  // không kiểm tra kết quả trả về
}

}  // namespace
}  // namespace ceres
