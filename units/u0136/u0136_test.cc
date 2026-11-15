// FILE: u0136_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetIsLessTest, TC1_P1_SequentialReturn) {
  using JetT = Jet<double, 2>;
  Eigen::Matrix<double, 2, 1> v;
  v << 0.5, 1.5;
  JetT f(3.7, v);
  JetT g(5.2, v);
  // Không kiểm tra kết quả trả về, chỉ gọi hàm một lần.
  (void)isless(f, g);
}

}  // namespace ceres
