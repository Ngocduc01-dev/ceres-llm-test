// FILE: u0138_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(IsLessEqualJetTest, P1_TwoJetsSameType) {
  Jet<double, 1> f(3.7, 0);
  Jet<double, 1> g(5.2, 0);
  bool result = islessequal(f, g);
  (void)result;  // Không kiểm tra kết quả trả về
}

}  // namespace
}  // namespace ceres
