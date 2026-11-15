// FILE: u0554_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/householder_vector.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0554, CallsTarget) {
  double v_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double beta_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  ComputeHouseholderVector({}, v_data, beta_data);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0554, CallsTargetAlternate) {
  double v_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double beta_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  ComputeHouseholderVector({}, v_data, beta_data);
}
}  // namespace internal
}  // namespace ceres
