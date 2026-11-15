// FILE: u0140_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsGreaterEqualJet, P1_SingleStatementPath) {
  // f.a = 2.5, g.a = -1.5 (chọn trong [-5, 5], giá trị cố định)
  Jet<double, 1> f(2.5);
  Jet<double, 1> g(-1.5);
  f.v[0] = 1.0;
  g.v[0] = 0.5;

  // Chỉ gọi hàm, không kiểm tra kết quả trả về
  (void)isgreaterequal(f, g);
}

}  // namespace
}  // namespace ceres
