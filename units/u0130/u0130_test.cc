// FILE: u0130_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(BesselJ1JetTest, P1_StraightLine) {
  Jet<double, 2> f(2.3, 0);
  Jet<double, 2> r = BesselJ1(f);
  (void)r;  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
