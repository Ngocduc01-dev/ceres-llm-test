// FILE: u0095_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// Path P1: START -> 1 -> END
TEST(JetNotEqualOperator, JetWithScalarStraightLine) {
  const Jet<double, 16> f(2.5);
  const double g = 3.7;
  const bool result = (f != g);
  (void)result;  // Không kiểm tra kết quả trả về.
}

}  // namespace
}  // namespace ceres
