// FILE: u0144_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Hàm IsFinite bị đánh dấu deprecated, tắt cảnh báo để tránh lỗi khi biên dịch với -Werror.
#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

// TC1 - P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(JetIsFiniteTest, TC1_P1_StraightLine) {
  ceres::Jet<double, 2> f(2.5, 0);
  ceres::IsFinite(f);
}
