// FILE: u0516_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/autodiff.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0516, CallsTarget) {
  double src_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double dst_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  Take1stOrderPart(1, src_data, dst_data);
}
}  // namespace internal
}  // namespace ceres
