// FILE: u0610_test.cc
#include "gtest/gtest.h"
#include "ceres/small_blas_generic.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0610, CallsTarget) {
  double a_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double b_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double c_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  MTV_mat4x1(1, a_data, 1, b_data, c_data, 1);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0610, CallsTargetAlternate) {
  double a_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double b_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double c_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  MTV_mat4x1(1, a_data, 1, b_data, c_data, 1);
}
}  // namespace internal
}  // namespace ceres
