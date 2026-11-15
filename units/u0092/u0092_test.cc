// FILE: u0092_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

namespace ceres {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetOperatorGreaterTest, TC1_ScalarComparisonPath) {
  const Jet<double, 7> f(3.5);
  const Jet<double, 7> g(-1.25);
  [[maybe_unused]] const bool result = f > g;
}

}  // namespace ceres
