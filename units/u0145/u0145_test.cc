// FILE: u0145_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Hàm IsNaN bị đánh dấu deprecated, tắt cảnh báo để tránh lỗi khi build với -Werror.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace ceres {

// TC1 - Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetIsNaNTest, TC1_P1_StraightLine) {
  Jet<double, 2> f(3.5, 0);
  bool result = IsNaN(f);
  static_cast<void>(result);  // Không kiểm tra kết quả trả về
}

}  // namespace ceres

#if defined(_MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
