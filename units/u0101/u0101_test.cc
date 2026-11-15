// FILE: u0101_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetLogTest, P1_SingleStraightPath) {
  Jet<double, 2> f;
  f.a = 2.3;
  f.v[0] = 1.7;
  f.v[1] = -3.1;

  Jet<double, 2> result = log(f);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
