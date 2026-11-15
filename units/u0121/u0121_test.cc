// FILE: u0121_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetHypot, P1_SingleStraightPath) {
  using JetT = Jet<double, 2>;

  JetT x(3.0);
  x.v[0] = 1.0;
  x.v[1] = 2.0;

  JetT y(4.0);
  y.v[0] = 5.0;
  y.v[1] = 3.0;

  JetT r = hypot(x, y);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
