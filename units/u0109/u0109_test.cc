// FILE: u0109_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetSinTest, TC1_P1_SinDouble7) {
  Jet<double, 7> f;
  f.a = 0.7;
  f.v[0] = 0.3;
  f.v[1] = -1.2;
  f.v[2] = 2.5;
  f.v[3] = 0.9;
  f.v[4] = -0.4;
  f.v[5] = 1.8;
  f.v[6] = -2.1;

  Jet<double, 7> r = sin(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
