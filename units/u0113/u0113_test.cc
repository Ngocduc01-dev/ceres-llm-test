// FILE: u0113_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetSinhTest, TC1_SinhDouble2) {
  Jet<double, 2> f;
  f.a = 0.7;
  f.v[0] = 1.3;
  f.v[1] = -0.4;

  Jet<double, 2> r = sinh(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
