// FILE: u0125_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetErfcTest, TC1_SingleStraightLinePath) {
  Jet<double, 2> x;
  x.a = 0.37;
  x.v[0] = -1.2;
  x.v[1] = 0.8;

  Jet<double, 2> r = erfc(x);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
