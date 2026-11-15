// FILE: u0105_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetExpm1Test, P1_SingleStraightPath) {
  Jet<double, 2> f;
  f.a = 1.3;
  f.v[0] = -2.1;
  f.v[1] = 3.4;

  Jet<double, 2> r = expm1(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
