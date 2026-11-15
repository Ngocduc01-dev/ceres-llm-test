// FILE: u0131_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BesselJnJetTest, SinglePathNoBranch) {
  const int n = 3;
  const Jet<double, 2> f(2.7, 0);
  Jet<double, 2> result = BesselJn(n, f);
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace internal
}  // namespace ceres
