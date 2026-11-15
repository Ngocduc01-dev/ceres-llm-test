// FILE: u0082_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorMinusScalarRight, NoBranchPath) {
  // Giá trị đã chọn ngẫu nhiên (seed cố định 42) trong khoảng [-10, 10].
  Jet<double, 4> f;
  f.a = 3.5;
  f.v[0] = 1.0;
  f.v[1] = -2.0;
  f.v[2] = 0.5;
  f.v[3] = 4.0;
  const double s = 1.25;

  Jet<double, 4> result = operator-(f, s);
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace internal
}  // namespace ceres
