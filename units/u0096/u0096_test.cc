// FILE: u0096_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsFinite, P1_TC1_NoBranch) {
  double x = 3.25;
  // Không kiểm tra kết quả trả về, chỉ gọi hàm một lần.
  (void)ceres::IsFinite(x);
}
