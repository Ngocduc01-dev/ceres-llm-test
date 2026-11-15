// FILE: u0089_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorDivideScalarTest, TC1_P1_DivideJetByScalar) {
  const Jet<double, 3> f(1.5, 1);
  const double s = 2.0;
  Jet<double, 3> r = f / s;
  (void)r;
}

}  // namespace
}  // namespace ceres
