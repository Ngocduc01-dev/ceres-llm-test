// FILE: u0093_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorGreaterEqual, JetWithIntScalar) {
  const Jet<double, 2> f(3.0, 0);
  const int g = 2;
  bool result = (f >= g);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
