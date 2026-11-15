// FILE: u0057_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/jet_traits.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(AsScalarTest, P1_ConstDoubleLvalue) {
  const double value = 3.5;
  // Không kiểm tra kết quả trả về, chỉ gọi hàm để đi qua đường P1.
  (void)ceres::internal::AsScalar<const double&>(value);
  SUCCEED();
}
