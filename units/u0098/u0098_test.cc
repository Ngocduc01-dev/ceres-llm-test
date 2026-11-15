// FILE: u0098_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Tắt cảnh báo deprecated vì hàm IsNaN được đánh dấu CERES_DEPRECATED_WITH_MSG.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsNaNTest, P1_StraightLine) {
  const double x = 3.5;  // chọn trong khoảng [-10, 10]
  (void)ceres::IsNaN(x);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
