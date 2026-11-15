// FILE: u0099_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// IsNormal bị đánh dấu deprecated, tắt cảnh báo để tránh lỗi khi build có -Werror.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsNormalTest, TC1_P1_StraightLine) {
  const double x = 37.5;
  (void)ceres::IsNormal(x);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
