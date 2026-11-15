// FILE: u0116_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(JetFloorTest, P1_NoBranch) {
  Jet<double, 2> f;
  f.a = 2.7;
  f.v[0] = 0.3;
  f.v[1] = -1.4;
  Jet<double, 2> r = floor(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
