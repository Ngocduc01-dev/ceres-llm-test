// FILE: u0091_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetLessEqualOperator, TC1_P1_SinglePath) {
  const Jet<double, 2> f(0.7);
  const Jet<double, 2> g(2.3);
  const bool result = (f <= g);
  static_cast<void>(result);  // Không kiểm tra kết quả trả về
}

}  // namespace ceres
