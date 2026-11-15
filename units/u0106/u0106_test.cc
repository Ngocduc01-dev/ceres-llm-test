// FILE: u0106_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(JetSqrtTest, TC1_P1_SinglePath) {
  Jet<double, 7> f;
  f.a = 6.0;
  f.v[0] = 3.0;
  f.v[1] = -7.0;
  f.v[2] = 1.0;
  f.v[3] = 9.0;
  f.v[4] = -2.0;
  f.v[5] = 5.0;
  f.v[6] = 8.0;

  Jet<double, 7> r = sqrt(f);
  (void)r;
}

}  // namespace internal
}  // namespace ceres
