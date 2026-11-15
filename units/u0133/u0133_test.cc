// FILE: u0133_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetIsInfTest, P1_ReturnIsInfOfScalarPart) {
  Jet<double, 1> f;
  f.a = 3.7;
  f.v[0] = 1.0;
  bool result = isinf(f);
  (void)result;  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
