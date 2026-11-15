// FILE: u0072_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {
namespace {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorPlusEqualScalar, P1_SequentialPath) {
  Jet<double, 2> a(3.5, 1);
  const double s = 2.25;
  a += s;
}

}  // namespace
}  // namespace ceres
