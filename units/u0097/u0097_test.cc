// FILE: u0097_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsInfinite, P1_SingleStatement) {
  const double x = 37.5;
  // Không kiểm tra kết quả trả về; chỉ gọi hàm để đi qua node 1.
  // Hàm bị đánh dấu deprecated nên tắt cảnh báo xung quanh lệnh gọi.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
  bool result = ceres::IsInfinite(x);
#if defined(_MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
  (void)result;
}
