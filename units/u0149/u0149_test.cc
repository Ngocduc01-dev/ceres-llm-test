// FILE: u0149_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(JetNormTest, P1_SingleStatementPath) {
  Jet<double, 2> f;
  f.a = 3.0;
  f.v[0] = -2.0;
  f.v[1] = 4.0;

  Jet<double, 2> r = ceres::norm(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
