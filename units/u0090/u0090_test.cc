// FILE: u0090_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorLessTest, P1_JetLessJet) {
  const Jet<double, 2> f(3.7, 0);
  const Jet<double, 2> g(6.2, 1);
  const bool result = f < g;
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace internal
}  // namespace ceres
