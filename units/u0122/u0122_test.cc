// FILE: u0122_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(JetHypot3Test, TC1_SingleStraightLinePath) {
  const Jet<double, 12> x(1.5, 0);
  const Jet<double, 12> y(2.0, 1);
  const Jet<double, 12> z(2.5, 2);

  const Jet<double, 12> r = hypot(x, y, z);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
