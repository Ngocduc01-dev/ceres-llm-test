// FILE: u0147_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

#if defined(_MSC_VER)
#pragma warning(disable : 4996)
#elif defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có nhánh nào)
TEST(IsInfiniteTest, P1_SingleStatement) {
  Jet<double, 2> f(3.7);
  f.v[0] = -12.5;
  f.v[1] = 41.2;
  bool result = IsInfinite(f);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace
}  // namespace ceres
