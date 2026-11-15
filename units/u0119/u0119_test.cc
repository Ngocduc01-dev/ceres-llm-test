// FILE: u0119_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetExp2, P1_NoBranch) {
  Jet<double, 2> f;
  f.a = 1.5;
  f.v[0] = 0.5;
  f.v[1] = -2.0;
  Jet<double, 2> r = exp2(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
