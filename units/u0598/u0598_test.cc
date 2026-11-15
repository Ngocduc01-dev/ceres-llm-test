// FILE: u0598_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/problem_impl.cc"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0598, CallsTarget) {
  double a_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double b_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  RegionsAlias(a_data, 1, b_data, 1);
}
}  // namespace internal
}  // namespace ceres
