// FILE: u0139_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có nhánh rẽ)
TEST(IslessgreaterTest, TC1_JetJet_P1) {
  Jet<double, 2> f(1.7, 0);
  Jet<double, 2> g(-3.2, 1);
  bool r = islessgreater(f, g);
  (void)r;  // không kiểm tra kết quả trả về
}

}  // namespace ceres
