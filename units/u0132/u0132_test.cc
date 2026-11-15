// FILE: u0132_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetIsFiniteTest, P1_SequentialReturn) {
  Jet<double, 1> f;
  f.a = 3.7;
  f.v[0] = 1.2;
  // Không kiểm tra kết quả trả về, chỉ gọi hàm để chạy qua node 1.
  (void)isfinite(f);
}

}  // namespace internal
}  // namespace ceres
