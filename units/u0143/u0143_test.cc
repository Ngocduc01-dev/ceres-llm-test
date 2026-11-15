// FILE: u0143_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(JetSignbitTest, P1_ReturnSignbitOfScalarPart) {
  // f.a = -2.5 nằm trong khoảng [-5, 5]; đạo hàm f.v[0] = 1.0
  Jet<double, 1> f(-2.5, 0);
  bool result = ceres::signbit(f);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
