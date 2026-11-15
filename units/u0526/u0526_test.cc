// FILE: u0526_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/eigen.h"
#include "ceres/invert_psd_matrix.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0526, CallsTarget) {
  InvertPSDMatrix(true, {});
}
}  // namespace internal
}  // namespace ceres
