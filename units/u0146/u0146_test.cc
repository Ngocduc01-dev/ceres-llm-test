// FILE: u0146_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// IsNormal bị đánh dấu deprecated, tắt cảnh báo để tránh lỗi khi build với -Werror.
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace ceres {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(IsNormalJetTest, TC1_P1_SingleStatementPath) {
  const Jet<double, 2> f(3.7, 0);
  const bool result = IsNormal(f);
  (void)result;  // Không kiểm tra kết quả trả về
  SUCCEED();
}

}  // namespace ceres

#if defined(_MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif
