// FILE: u0117_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(JetCeilTest, P1_StraightLine) {
  Jet<double, 2> f;
  f.a = 2.37;
  f.v[0] = 0.5;
  f.v[1] = -1.25;

  Jet<double, 2> r = ceil(f);
  (void)r;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
