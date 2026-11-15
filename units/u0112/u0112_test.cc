// FILE: u0112_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetAtanTest, P1_NoBranch) {
  Jet<double, 2> f;
  f.a = 0.7;
  f.v[0] = 0.3;
  f.v[1] = -1.2;

  Jet<double, 2> r = atan(f);
  (void)r;  // Không kiểm tra kết quả trả về.
}

}  // namespace
}  // namespace ceres
