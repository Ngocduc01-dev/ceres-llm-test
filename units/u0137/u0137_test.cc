// FILE: u0137_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsGreaterJetTest, P1_JetDouble2_SinglePath) {
  const Jet<double, 2> f(3.7, 0);
  const Jet<double, 2> g(-1.2, 1);
  bool result = isgreater(f, g);
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace ceres
