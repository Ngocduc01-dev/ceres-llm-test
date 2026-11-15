// FILE: u0094_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorEqualTest, P1_SinglePath) {
  using JetT = Jet<double, 2>;
  JetT f(3.0, 0);
  JetT g(5.0, 1);
  bool result = (f == g);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace
}  // namespace ceres
