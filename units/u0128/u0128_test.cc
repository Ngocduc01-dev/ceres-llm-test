// FILE: u0128_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BesselJnTest, SinglePath) {
  const int n = 3;
  const double x = 2.7;
  double result = ceres::BesselJn(n, x);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
